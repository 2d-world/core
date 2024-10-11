#pragma once

#include <stddef.h>

void *t_nonnull(void *ptr);
void *t_malloc(size_t size);
void *t_realloc(void *ptr, size_t size);
void *t_memdup(const void *ptr, size_t size);
char *t_strdup(const char *str);
