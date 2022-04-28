#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Replacement for malloc that stores the pointers allocated.
void *talloc(size_t size){

}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated in lists to hold those pointers.
void tfree();

// Replacement for the C function "exit", that consists of two lines: it calls
// tfree before calling exit.
void texit(int status);