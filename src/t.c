#include "t.h"

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
  TInternal result = {{map}, T_STATE_PREPARE};

  TMap_insert(map, "builtin.util.t_nonnull", (void *)&t_nonnull, NULL);
  TMap_insert(map, "builtin.util.t_malloc", (void *)&t_malloc, NULL);
  TMap_insert(map, "builtin.util.t_realloc", (void *)&t_realloc, NULL);
  TMap_insert(map, "builtin.util.t_memdup", (void *)&t_memdup, NULL);
  TMap_insert(map, "builtin.util.t_strdup", (void *)&t_strdup, NULL);

  TMap_insert(map, "builtin.TMap.new", (void *)&TMap_new, NULL);
  TMap_insert(map, "builtin.TMap.insert", (void *)&TMap_insert, NULL);
  TMap_insert(map, "builtin.TMap.search", (void *)&TMap_search, NULL);
  TMap_insert(map, "builtin.TMap.delete", (void *)&TMap_delete, NULL);

  static const int VERSION = 0; // TODO: increse on release
  TMap_insert(map, "version", (void *)&VERSION, NULL);

  return t_memdup(&result, sizeof(result));
}

DLLEXPORT err_t tRegisterPlugin(T self, TPlugin plugin) {
  if (((TInternal *)self)->state != T_STATE_PREPARE)
    abort();
  return plugin(self, NULL);
}

DLLEXPORT err_t tStart(T self) {
  if (((TInternal *)self)->state != T_STATE_PREPARE)
    abort();
  ((TInternal *)self)->state = T_STATE_STARTED;
  err_t (*const mainLoop)(T self) =
      (err_t(*)(T))TMap_search(self->map, "mainLoop");
  if (!mainLoop) {
    return 1;
  }
  return mainLoop(self);
}
