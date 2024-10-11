#include "util.h"

#include <stdlib.h>
#include <string.h>

void *t_nonnull(void *ptr) {
  if (!ptr) {
    abort();
  }
  return ptr;
}

void *t_malloc(size_t size) { return t_nonnull(malloc(size)); }

void *t_realloc(void *ptr, size_t size) {
  return t_nonnull(realloc(ptr, size));
}

void *t_memdup(const void *ptr, size_t size) {
  void *const result = t_malloc(size);
  memcpy(result, ptr, size);
  return result;
}

char *t_strdup(const char *str) { return t_memdup(str, strlen(str) + 1); }
