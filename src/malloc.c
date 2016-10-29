#include "malloc.h"

static struct block *g_blocks = NULL;

__attribute__((__visibility__("default")))
void *malloc(size_t size)
{
  if (size == 0)
    return NULL;
  if (!g_blocks)
    init_g();
  size += sizeof (struct block);
  size = round_ptwo(size);
  size = size < g_MIN_SIZE_BLOCK ? g_MIN_SIZE_BLOCK : size;
  struct block *b = get_block(size);
  if (b)
  {
    if (b->size != size) 
      divide(b, size);
    b->free = 0;
  }
  return ptr_data(b);
}

struct block *get_block(size_t size)
{
  if (size > g_MAX_SIZE_BLOCK)
    add_block(size);
  struct block *b = g_blocks;
  while (b)
  {
    if (b->free && b->size >= size)
      return b;
    b = b->next;
  }
  if (add_block(g_MAX_SIZE_BLOCK) == -1)
    return NULL;
  return get_block(size);
}

int add_block(size_t size)
{
  struct block *new_buddy = NULL;
  new_buddy = mmap(0, size, g_prot, g_flags, -1, 0);
  if (new_buddy == MAP_FAILED)
    return -1;
  init_block(new_buddy, 1, size, g_blocks);
  g_blocks = new_buddy;
  return 0;
}
