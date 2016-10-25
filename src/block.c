#include "block.h"

void *ptr_data(struct block *b)
{
  return (void*) b ^ sizeof(struct block);
}

void divide(struct block *b)
{
  if (!b->free)
    return;
  b->size /= 2;
  struct block *buddy = b ^ b->size;
  init_block(buddy, 1, b->size, b->next);
  b->next = buddy;
}

void init_block(struct block *b, char free, size_t size, struct block *next)
{
  if (!b)
    return;
  b->free = free;
  b->size = size;
  b->next = next;
}
