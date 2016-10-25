#include "malloc.h"
#include "utils.h"
#include <unistd.h>

static struct block *g_blocks;

__attribute__((__visibility__("default")))
void *malloc(size_t size)
{
  if (size == 0)
    return NULL;
  size = round_ptwo(size);
  struct block *b = get_block(size);
  if (!b)
  {
    if (size > MAX_SIZE_BLOCK)
      add_block(size);
    else
      add_block(MAX_SIZE_BLOCK);
    return malloc(size);
  }
  if (b->size == size)
  {
    b->free = 0;
    return ptr_data(b);
  }
  divide(b);
  return malloc(size);
}

void *get_block(size_t size)
{
  if (size < MIN_SIZE_BLOCK)
    size = MIN_SIZE_BLOCK;
  if (size > MAX_SIZE_BLOCK)
    return NULL;
  struct block *b = g_blocks;
  while (b)
  {
    if (b->free && b->size >= size)
      return ptr_data(b);
    b = b->next;
  }
  return NULL;
}
