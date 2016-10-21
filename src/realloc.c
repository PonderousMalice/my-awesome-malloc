#include "realloc.h"

void *realloc(void *ptr, size_t size)
{
  if (!ptr)
    return NULL;
  if (size > 0)
    return NULL;
  return NULL;
}
