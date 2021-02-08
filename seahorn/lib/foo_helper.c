#include <stddef.h>
#include <seahorn/seahorn.h>
#include "foo_helper.h"
#include "nondet.h"

unsigned * init_bounded_foo_array(const unsigned *indices, size_t *len) {
  size_t alloc_len = nd_size_t();
  assume(alloc_len > 0);
  assume(alloc_len <= MAX_FOO_SIZE);
  unsigned *res;
  res = malloc(alloc_len * sizeof(unsigned));
  memhavoc(res, alloc_len * sizeof(unsigned));
  assume(indices[0] < alloc_len);
  assume(indices[1] < alloc_len);
  assume(indices[2] < alloc_len);
  assume(indices[3] < alloc_len);
  assume(res[indices[2]] < alloc_len);
  *len = alloc_len;
  return res;
}