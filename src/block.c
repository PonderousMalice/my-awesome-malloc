#include "block.h"

void init_g()
{
  g_MAX_SIZE_BLOCK = sysconf(_SC_PAGESIZE);
  g_MIN_SIZE_BLOCK = round_ptwo(sizeof (struct block));
}

void *ptr_data(struct block *b)
{
  if (!b)
    return NULL;
  union ublock block;
  block.ptr = b;
  block.uint += sizeof (struct block);
  return block.ptr;
}

void divide(struct block *b, size_t size)
{
  if (!b->free || b->size == size || b-> size == g_MIN_SIZE_BLOCK)
    return;
  b->size >>= 1;
  struct block *buddy = get_buddy(b);
  init_block(buddy, 1, b->size, b->next);
  b->next = buddy;
  divide(b, size);
}

void merge(struct block *b, size_t size)
{
  if (b->size >= size)
    return;
  struct block *buddy = get_buddy(b);
  if (buddy->free)
  {
    if (b->next == buddy)
    {
      b->size <<= 1;
      b->next = buddy->next;
    }
    else
    {
      buddy->size <<= 1;
      buddy->next = b->next;
    }
  }
}

void init_block(struct block *b, char free, size_t size, struct block *next)
{
  if (!b)
    return;
  b->free = free;
  b->size = size;
  b->next = next;
}

struct block *get_buddy(struct block *b)
{
  union ublock block;
  union ublock buddy;
  block.ptr = b;
  buddy.uint = block.uint ^ b->size;
  return buddy.ptr;
}

struct block *get_theorical_buddy(struct block *b, size_t b_size)
{
  union ublock block;
  union ublock buddy;
  block.ptr = b;
  buddy.uint = block.uint ^ b_size;
  return buddy.ptr;
}
