#pragma once
#include <stddef.h>

#ifndef MAX_FOO_SIZE
#define MAX_FOO_SIZE 16
#endif

unsigned * init_bounded_foo_array(const unsigned *indices, size_t *len);
