#ifndef MY_MALLOC
# define MY_MALLOC
# include <stddef.h>
# include "block.h"

void *malloc(size_t size);
void *get_block(size_t size);
#endif
