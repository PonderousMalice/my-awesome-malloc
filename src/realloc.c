#include "realloc.h"

__attribute__((__visibility__("default")))
void *realloc(void *ptr, size_t size)
{
  if (size == 0)
    return NULL;
  size += sizeof (struct block);
  size = round_ptwo(size);
  if (!ptr || size > g_MAX_SIZE_BLOCK)
    return malloc(size);
  struct block *b = ptr;
  b--;
  if (b->size >= size)
    return ptr;
  size_t max_available = max_free_b(b);
  if (max_available < size)
  {
    struct block *res = malloc(size);
    res = memcpy(res, ptr, b->size - sizeof (struct block));
    free(ptr);
    return res;
  }
  merge(b, g_MAX_SIZE_BLOCK);
  return ptr;
 }
