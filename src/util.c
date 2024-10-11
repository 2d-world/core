#include "util.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

err_t t_malloc(size_t size, void **dest) {
  void *const result = malloc(size);
  if (result) {
    *dest = result;
    return false;
  }
  return true;
}

err_t t_realloc(void *ptr, size_t size, void **dest) {
  void *const result = realloc(ptr, size);
  if (result) {
    *dest = result;
    return false;
  }
  return true;
}

err_t t_memdup(const void *ptr, size_t size, void **dest) {
  void *const result = malloc(size);
  if (result) {
    memcpy(result, ptr, size);
    *dest = result;
    return false;
  }
  return true;
}

err_t t_strdup(const char *str, char **dest) {
  return t_memdup(str, strlen(str) + 1, (void **)dest);
}
