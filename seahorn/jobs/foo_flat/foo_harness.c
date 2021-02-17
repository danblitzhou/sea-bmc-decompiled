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

int main(void) {

  // -- prophecy variables for the results of each function
  unsigned res_o = nd_size_t();
  unsigned res_d = nd_size_t();

  // -- a pointer into memory
  uint8_t *p = nd_voidp();
  // -- prophecy variables for a value of a byte of memory at address p
  uint8_t byte_at_p_o = nd_uint8_t();
  uint8_t byte_at_p_d = nd_uint8_t();

  // -- first function argument -- a pointer into memory
  unsigned *arr_a = nd_voidp();
  // -- second function argument -- a pointer into memory
  unsigned *indices_a = nd_voidp();

  // -- fork and run the functions from exactly the same branch
  // -- the branches are exclusive, but they are actually run in parallel
  if (nd_bool()) {
    unsigned res = foo(arr_a, indices_a);
    // -- the assumptions are at a global scope, they do not depend on the path
    // -- condition. Thus, they establish the value of prophecy variables
    assume(res_o == res);
    assume(byte_at_p_o == *p);
  } else {
    unsigned res = foo_decompiled(arr_a, indices_a);
    // -- the assumptions are at a global scope. See comment in the other branch
    assume(res_d == res);
    assume(byte_at_p_d == *p);
  }

  // -- check that prophecy variables are equivalent
  sassert(res_o == res_d);
  sassert(byte_at_p_o == byte_at_p_d);


  return 0;
}
