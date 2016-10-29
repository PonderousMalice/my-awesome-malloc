#include "free.h"

__attribute__((__visibility__("default")))
void free(void *ptr)
{
  if (!ptr)
    return;
  union ublock block;
  block.ptr = ptr;
  block.uint -= sizeof (struct block);
  struct block *b = block.ptr;
  b->free = 1;
  merge(b, g_MAX_SIZE_BLOCK);
}
