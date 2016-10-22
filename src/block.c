#include "block.h"
#include <sys/mman.h>

void init_mdata(struct metadata *m, char free, size_t size, struct metadata *n)
{
  if (!m)
    return;
  m->free = free;
  m->size = size;
  m->next_free = n;
}

void init_page(struct page *p, size_t size, struct page *next)
{
  if (!p)
    return;
  p->size = size - sizeof (struct page);
  p->next = next;
  struct metadata *tmp = (struct metadata*) ((char *) p + sizeof (struct page));
  init_mdata(tmp, 1, p->size - sizeof (struct metadata), NULL);
  p->nt_free = tmp;
}

void add_page(struct page *l, struct page *new_p)
{
  if (!l)
    return;
  while(l->next)
    l = l->next;
  l->next = new_p; 
}

struct page *create_page(size_t size)
{
  int prot = PROT_READ | PROT_WRITE;
  int flags = MAP_ANONYMOUS | MAP_PRIVATE;
  void *res = mmap(NULL, size, prot, flags, -1, 0);
  init_page(res, size, NULL);
  return res; 
}
