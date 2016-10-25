#ifndef BLOCK
# define BLOCK
# define MAX_SIZE_BLOCK 4096
# define MIN_SIZE_BLOCK 8
# define _DEFAULT_SOURCE
# include <stddef.h>

struct block 
{
  char free;
  size_t size;
  struct block *next;
};

void divide(struct block *b);
void *ptr_data(struct block *b);
void init_block(struct block *b, char free, size_t size, struct block *next);
#endif
