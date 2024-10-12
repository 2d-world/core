#pragma once

#if _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

typedef _Bool err_t;

// write once, read only map
typedef struct TMap *TMap;
DLLEXPORT TMap TMap_new(void);
DLLEXPORT err_t TMap_insert(TMap map, const char *key, void *value,
                            void (*deleteValue)(void *value));
DLLEXPORT void *TMap_search(TMap map, const char *key);
DLLEXPORT void TMap_delete(TMap self);

typedef struct T {
  TMap map;
} *T;

struct THandle {
  void (*free)(void *actual_handle);
  void *actual_handle;
};
typedef err_t (*TPlugin)(T context);

DLLEXPORT T tInit(void);
DLLEXPORT err_t tRegisterPlugin(T self, TPlugin plugin);
DLLEXPORT err_t tStart(T self);
DLLEXPORT void tDestroy(T self);
