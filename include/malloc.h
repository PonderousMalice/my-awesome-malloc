#ifndef MY_MALLOC
# define MY_MALLOC
# include <stddef.h>
# include "block.h"

void *malloc(size_t size);
struct block *get_block(size_t size);
void add_block(size_t size)
#endif
