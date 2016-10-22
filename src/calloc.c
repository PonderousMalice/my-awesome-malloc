#include "calloc.h"

__attribute__((__visibility__("default")))
void *calloc(size_t number, size_t size)
{
  size_t tmp = number + size;
  if (!tmp)
    return NULL;
  return NULL;
}
