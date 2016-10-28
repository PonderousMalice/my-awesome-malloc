#include "block.h"

void init_g()
{
  g_MAX_SIZE_BLOCK = sysconf(_SC_PAGESIZE);
  g_MIN_SIZE_BLOCK = round_ptwo(sizeof (struct block));
}

void *ptr_data(struct block *b)
{
  return b ? ++b : NULL;
}

void divide(struct block *b, size_t size)
{
  if (!b->free || b->size == size || b-> size == g_MIN_SIZE_BLOCK)
    return;
  b->size >>= 1;
  uintptr_t b_adr = b;
  uintptr_t b_size = b->size;
  uintptr_t adr_buddy = b_adr ^ b_size;
  struct block *buddy = adr_buddy;
  init_block(buddy, 1, b->size, b->next);
  b->next = buddy;
  divide(b, size);
}

void merge(struct block *b)
{
  if (b->size == g_MAX_SIZE_BLOCK)
    return;
  uintptr_t b_adr = b;
  uintptr_t b_size = b->size;
  uintptr_t adr_buddy = b_adr ^ b_size;
  struct block *buddy = adr_buddy;
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

void init_block(struct block *b, char free, size_t size, struct block *next)
{
  if (!b)
    return;
  b->free = free;
  b->size = size;
  b->next = next;
}
