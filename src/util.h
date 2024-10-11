#pragma once

#include <stddef.h>

typedef _Bool err_t;

err_t t_malloc(size_t size, void **dest);
err_t t_realloc(void *ptr, size_t size, void **dest);
err_t t_memdup(const void *ptr, size_t size, void **dest);
err_t t_strdup(const char *str, char **dest);
