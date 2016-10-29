#include "realloc.h"

__attribute__((__visibility__("default")))
void *realloc(void *ptr, size_t size)
{
  if (!ptr)
    return NULL;
  if (size > 0)
    return NULL;
  return NULL;
}
