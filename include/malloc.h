#ifndef MY_MALLOC
# define MY_MALLOC
# include "block.h"
# include "utils.h"
# include <stddef.h>
# include <sys/mman.h>

extern size_t g_MAX_SIZE_BLOCK;
extern size_t g_MIN_SIZE_BLOCK;

static const int g_flags = MAP_ANONYMOUS | MAP_PRIVATE;
static const int g_prot = PROT_READ | PROT_WRITE;

void *malloc(size_t size);
struct block *get_block(size_t size);
int add_block(size_t size);
#endif
