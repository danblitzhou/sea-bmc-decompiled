#include "assert_helpers.h"

// -- defines sassert and assume
#include <seahorn/seahorn.h>

// -- defined nd_XXX functions
#include "nondet.h"

void assert_mem_eq(uint8_t *mem1, uint8_t *mem2, size_t sz) {
  // -- compare a non-deterministically chosen byte of mem1 and mem2
  size_t p = nd_size_t();
  assume(p < sz);

  // -- if mem1 and mem2 differ, this assertion will fail
  sassert(mem1[p] == mem2[p]);
}
