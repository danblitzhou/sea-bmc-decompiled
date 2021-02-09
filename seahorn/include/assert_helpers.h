#pragma once
#include <stdint.h>
#include <stdlib.h>

/**
   Asserts that two given memory regions are byte-equivalent

   @param mem1 pointer to the first memory region
   @param mem2 pointer to the second memory region
   @param sz   number of bytes to compare

   Triggers sassert if mem1 and mem2 differ at some byte
 */
void assert_mem_eq(uint8_t *mem1, uint8_t *mem2, size_t sz);
