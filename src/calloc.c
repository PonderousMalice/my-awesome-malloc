#include "calloc.h"

void *calloc(size_t number, size_t size)
{
  size_t tmp = number + size;
  if (!tmp)
    return NULL;
  return NULL;
}
