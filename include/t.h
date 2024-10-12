#pragma once

typedef _Bool err_t;

// write once, read only map
typedef struct TMap *TMap;
typedef TMap (*TMap_new)(void);
typedef err_t (*TMap_insert)(TMap map, const char *key, void *value,
                             void (*deleteValue)(void *value));
typedef void *(*TMap_search)(TMap map, const char *key);
typedef void (*TMap_delete)(TMap self);

typedef struct T {
  TMap map;
} *T;

struct THandle {
  void (*free)(void *actual_handle);
  void *actual_handle;
};
typedef err_t (*TPlugin)(T context, TMap_search search);

typedef T (*tInit)(void);
typedef err_t (*tRegisterPlugin)(T self, TPlugin plugin);
typedef err_t (*tStart)(T self);
typedef void (*tDestroy)(T self);
