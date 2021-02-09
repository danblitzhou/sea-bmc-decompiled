#include <stdlib.h>
#include <string.h>

// -- defines sassert and assume
#include <seahorn/seahorn.h>

// -- defined nd_XXX functions
#include "nondet.h"
#include "assert_helpers.h"
// -- functions being compared
#include "foo.h"

// -- array initialization
#include "foo_helper.h"

unsigned *init_bounded_foo_array(const unsigned *indices, size_t *len) {
  size_t alloc_len = nd_size_t();
  assume(alloc_len >= 2);
  assume(alloc_len <= MAX_FOO_SIZE);
  unsigned *res;
  res = malloc(alloc_len * sizeof(unsigned));
  memhavoc(res, alloc_len * sizeof(unsigned));
  assume(indices[0] < alloc_len);
  assume(indices[1] < alloc_len);
  assume(indices[2] < alloc_len);
  assume(indices[3] < alloc_len);
  assume(res[indices[2]] < alloc_len);
  assume(res[indices[0]] < alloc_len * 8);
  *len = alloc_len;
  return res;
}

int main(void) {
  // indices is an array of 4
  unsigned indices_a[4];
  memhavoc(indices_a, sizeof(indices_a));

  size_t len;
  unsigned *arr_a = init_bounded_foo_array(indices_a, &len);

  size_t arr_b_size = len * sizeof(unsigned);
  unsigned *arr_b = malloc(arr_b_size);

#ifdef USE_MEMCPY
  // under lambdas
  memcpy(arr_b, arr_a, arr_b_size);
#else
  // requires a large unroll which slows down verification
  memhavoc(arr_b, arr_b_size);
  assume(bcmp(arr_a, arr_b, arr_b_size) == 0);
#endif

  /* operation under verification */
  unsigned res_o = foo(arr_a, indices_a);
  unsigned res_d = foo_decompiled(arr_b, indices_a);

  // -- check result
  sassert(res_o == res_d);
  // -- check memory that was modified
  assert_mem_eq((uint8_t *)arr_a, (uint8_t *)arr_b, arr_b_size);

  return 0;
}
