#include "utils.h"

size_t round_ptwo(size_t nb)
{
  if (is_pow_two(nb))
    return nb;
  size_t res = 1;
  while (res < nb)
    res <<= 1;
  return res;
}

int is_pow_two(size_t nb)
{
  return !(nb & (nb - 1));
}
