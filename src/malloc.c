#include "malloc.h"
#include <unistd.h>

static struct page *g_pages = NULL;
static long g_page_size = 0;
static size_t g_max_size = 0;

__attribute__((__visibility__("default")))
void *malloc(size_t size)
{
  if (!g_page_size)
  {
    g_page_size = sysconf(_SC_PAGESIZE);
    g_max_size = g_page_size - (sizeof (struct page) + sizeof (struct metadata)); 
  }
  void *res = NULL;
  if (size == 0)
    return res;
  if (size > g_max_size)
  {
    // to implement
    return res;
  }
  if (!g_pages)
    g_pages = create_page(g_page_size);
  res = get_block(size);
  alloc(g_pages, res, size);
  if (res)
    res = (char *) res + sizeof (struct metadata);
  return res;
}

void *get_block(size_t size)
{
  struct page *list = g_pages;
  while (list)
  {
    struct metadata *block = (struct metadata*) ((char *) list + sizeof (struct page));
    while (block)
    {
      if (block->free && block->size >= size)
        return block;
      block = block->next_free;
    }
    list = list->next;
  }
  return NULL;
}

void alloc(struct page *p, void *adr, size_t size)
{
  if (!adr || !p)
    return;
  struct metadata *block =  (struct metadata*) adr;
  struct metadata *free_b = (struct metadata *) ((char *) adr + sizeof (struct metadata) + size);
  size_t size_fb = block->size - size - sizeof (struct metadata); 
/*  
  if (!p->nt_free || p->nt_free > )
  {
    next_free = p->nt_free;
    p->nt_free = ptr;
  }
*/
  init_mdata(free_b, 1, size_fb, NULL); 
  init_mdata(block, 0, size, NULL);
}
