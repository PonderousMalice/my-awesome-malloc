#include "calloc.h"

__attribute__((__visibility__("default")))
void *calloc(size_t number, size_t size)
{
  if (!number || !size)
    return NULL;
  void *res = malloc(size * number);
  res = memset(res, 0, size * number);
  return res;
}
