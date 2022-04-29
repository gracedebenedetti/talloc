#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "linkedlist.h"
#include "value.h"

//global variable head
Value* listHead;

// Replacement for malloc that stores the pointers allocated.
void *talloc(size_t size){
    *listHead = malloc(size);
    //not sure if this list has Value ptrs or not
    Value* nextCell = malloc(size);
    //definitely not right but trying
    (*cell).next = *nextCell;
    return pointerList
}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated in lists to hold those pointers.
void tfree();
    Value* cur = list;
    while (!isNull(listHead)){
        Value *next = listHead.next;
        free(list);
        cur = next;
    }
    free(cur);

// Replacement for the C function "exit", that consists of two lines: it calls
// tfree before calling exit.
void texit(int status);
    tfree();
    exit();