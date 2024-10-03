#pragma once

typedef struct T *T;
typedef _Bool err_t;

T tInit();
err_t tRegisterPlugin(T self, void *plugin);
err_t tStart(T self);
void tDestroy(T self);
