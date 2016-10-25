#include "malloc.h"
#include "utils.h"
#include <sys/mman.h>
#include <unistd.h>

static const int g_flags = MAP_ANONYMOUS | MAP_PRIVATE;
static const int g_prot = PROT_READ | PROT_WRITE;
static struct block *g_blocks;

__attribute__((__visibility__("default")))
void *malloc(size_t size)
{
  if (size == 0)
    return NULL;
  size = round_ptwo(size);
  size = size < MIN_SIZE_BLOCK ? MIN_SIZE_BLOCK : size;
  struct block *b = get_block(size);
  if (!b)
    add_block(MAX_SIZE_BLOCK);
  else
  {
    if (b->size == size)
    {
      b->free = 0;
      return ptr_data(b);
    }
    divide(b);
  }
  return malloc(size);
}

struct block *get_block(size_t size)
{
  if (size > MAX_SIZE_BLOCK)
    add_block(size);
  struct block *b = g_blocks;
  while (b)
  {
    if (b->free && b->size >= size)
      return b;
    b = b->next;
  }
  return NULL;
}

void add_block(size_t size)
{
  struct block *new_buddy = NULL;
  new_buddy = mmap(0, size, g_prot, g_flags, -1, 0);
  init_block(new_buddy, 1, size, g_blocks);
  g_blocks = new_buddy;
}
