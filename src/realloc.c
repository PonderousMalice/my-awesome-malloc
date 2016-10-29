#include "realloc.h"

__attribute__((__visibility__("default")))
void *realloc(void *ptr, size_t size)
{
  if (size == 0)
    return NULL;
  if (!ptr)
    return malloc(size);
  struct block *b = ptr;
  size = round_ptwo(size);
  if (b->size >= size)
    return ptr;
  size_t max_available = max_free_b(b);
  if (max_available < size)
  {
    struct block *res = malloc(size);
    res = memcpy(res, ptr, b->size);
    res->size = size;
    free(ptr);
    return res;
  }
  merge(b, size);
  return ptr;
}
