#ifndef MY_REALLOC
# define MY_REALLOC
# include "free.h"
# include "malloc.h"
# include "utils.h"
# include <string.h>

extern size_t g_MAX_SIZE_BLOCK;
extern size_t g_MIN_SIZE_BLOCK;

void *realloc(void *ptr, size_t size);
#endif
