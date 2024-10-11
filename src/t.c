#include "t.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "util.h"

typedef enum TState {
  T_STATE_PREPARE,
  T_STATE_STARTED,
} TState;

typedef struct TInternal {
  struct T toExpose;
  TState state;
} TInternal;

DLLEXPORT T tInit() {
  const TMap map = TMap_new();
  TInternal internal = {{map}, T_STATE_PREPARE};

  TMap_insert(map, "builtin.util.t_malloc", (void *)&t_malloc, NULL);
  TMap_insert(map, "builtin.util.t_realloc", (void *)&t_realloc, NULL);
  TMap_insert(map, "builtin.util.t_memdup", (void *)&t_memdup, NULL);
  TMap_insert(map, "builtin.util.t_strdup", (void *)&t_strdup, NULL);

  static const int VERSION = 0; // TODO: increse on release
  TMap_insert(map, "version", (void *)&VERSION, NULL);

  T result;
  if (t_memdup(&internal, sizeof(internal), (void **)&result)) {
    return NULL;
  }
  return result;
}

DLLEXPORT err_t tRegisterPlugin(T self, TPlugin plugin) {
  if (((TInternal *)self)->state != T_STATE_PREPARE)
    return true;
  return plugin(self, NULL);
}

DLLEXPORT err_t tStart(T self) {
  if (((TInternal *)self)->state != T_STATE_PREPARE)
    return true;
  ((TInternal *)self)->state = T_STATE_STARTED;
  err_t (*const mainLoop)(T self) =
      (err_t(*)(T))TMap_search(self->map, "mainLoop");
  if (!mainLoop) {
    return true;
  }
  return mainLoop(self);
}
