#ifndef BLOCK
# define BLOCK
# include <stddef.h>
# define _DEFAULT_SOURCE

struct metadata
{
  char free;
  size_t size;
  struct metadata *next_free;
};

struct page
{
  size_t size;
  struct page *next;
  struct metadata *nt_free;
};

void init_mdata(struct metadata *m, char free, size_t size, struct metadata *n);
void init_page(struct page *p, size_t size, struct page *next);
void add_page(struct page *l, struct page *new_p);
struct page *create_page(size_t size);
#endif
