#ifndef BLOCK
# define BLOCK
# define _DEFAULT_SOURCE
# include "utils.h"
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>

size_t g_MAX_SIZE_BLOCK;
size_t g_MIN_SIZE_BLOCK;

union ublock
{
  uintptr_t uint;
  struct block *ptr;
};

struct block
{
  char free;
  size_t size;
  struct block *next;
};

struct block *get_buddy(struct block *b);
void *ptr_data(struct block *b);
void divide(struct block *b, size_t size);
void init_block(struct block *b, char free, size_t size, struct block *next);
void init_g();
void merge(struct block *b);
#endif
