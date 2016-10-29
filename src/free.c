#include "free.h"

__attribute__((__visibility__("default")))
void free(void *ptr)
{
  if (!ptr)
    return;
  struct block *b = ptr;
  b--;
  b->free = 1;
  merge(b, g_MAX_SIZE_BLOCK);
}
