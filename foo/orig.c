#include "foo.h"

unsigned foo(unsigned* arr, unsigned* indices) {
    int x = arr[0];
    int y = arr[1];
    arr[indices[1]] = arr[indices[0]] / 8;
    arr[indices[3]] = arr[arr[indices[2]]] + y;
    if (arr[indices[1]] == x) {
        arr[indices[1]] = 42;
    }
    return arr[0];
}
