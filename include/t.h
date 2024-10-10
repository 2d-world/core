#pragma once

#if _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

typedef struct T *T;
typedef _Bool err_t;

struct THandle {
  void (*free)(void *actual_handle);
  void *actual_handle;
};
typedef struct THandle *(*TOn)(T context, const char *event_name, void *args);
typedef err_t (*TPlugin)(T context, TOn on);

DLLEXPORT T tInit();
DLLEXPORT err_t tRegisterPlugin(T self, TPlugin plugin);
DLLEXPORT err_t tStart(T self);
DLLEXPORT void tDestroy(T self);
