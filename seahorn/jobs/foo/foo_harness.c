#include <seahorn/seahorn.h>
#include <strings.h>
#include <stdlib.h>
#include "nondet.h"
#include "foo.h"
#include "foo_helper.h"

int main(void) {
  // indices is an array of 4
  unsigned indices_a[4];
  memhavoc(indices_a, sizeof(indices_a));
  size_t len;
  unsigned *arr_a = init_bounded_foo_array(indices_a, &len);

  unsigned *arr_b = malloc(len * sizeof(unsigned));

  assume(bcmp(arr_a, arr_b, len * sizeof(unsigned)) == 0);

  /* operation under verification */
  foo(arr_a, indices_a);
  foo_decompiled(arr_b, indices_a);

  size_t i = nd_size_t();
  assume(i < len * sizeof(unsigned));
  assume(i >= 0);
  sassert(((uint8_t*)arr_a)[i] == ((uint8_t*)arr_b)[i]);
  return 0;
}
