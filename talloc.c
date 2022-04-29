#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"

//global variable head

// Basically what this variable does is it keeps track of the head of the list.
// However, you're not allowed to have pointers as global variables,
// so this one is an object literal which *points* to the head of the list.
//
// If the list is empty, then the cdr of the listHead will be NULL. (Which it is by default)
// If the list has items, then the cdr of the listHead will *point* to the head of the list,
// which can then be used as normal.
//
// This is confusing af so just give me a call if you're confused
Value listHead = (Value){.type = CONS_TYPE, .c = (struct ConsCell){.car = NULL, .cdr = NULL}};


// Returns a pointer to the next item in the list of Values
Value* nextVal(Value* list){
    assert(list->type == CONS_TYPE); // must be a cons type
    return list->c.cdr;
}

// Returns a new NULL_TYPE node.
// Remember to free any nullNode's we create!
Value* nullNode()
{
    Value* newNullNode = (Value*)malloc(sizeof(Value));
    newNullNode->type = NULL_TYPE;
    return newNullNode;
}

// Replacement for malloc that stores the pointers allocated.
void *talloc(size_t size){
    void* newPtr = malloc(size); // This is the new pointer being malloc'd by the user

    Value* newConsNode = (Value*)malloc(sizeof(Value));
    newConsNode->type = CONS_TYPE;

    Value* newPtrNode = (Value*)malloc(sizeof(Value));
    newPtrNode->type = PTR_TYPE;

    newPtrNode->p = newPtr; // assigns the pointer to the new PTR_TYPE node

    newConsNode->c.car = newPtrNode; // assigns the new PTR_TYPE node to the car of the new CONS_TYPE node

    if (listHead.c.cdr != NULL) // if list is nonempty, add to list.
    {
        newConsNode->c.cdr = listHead.c.cdr;
        listHead.c.cdr = newConsNode;
    } else // if list is empty, add to the listHead.
    {
        newConsNode->c.cdr = nullNode();
        listHead.c.cdr = newConsNode;
    }
    return newPtr;
}

// Free all pointers allocated by talloc, as well as whatever memory you
// allocated in lists to hold those pointerse.
void tfree(){
    Value* headPtr;
    if (listHead.c.cdr != NULL) // only need to free memory if the list is nonempty
    {
        headPtr = listHead.c.cdr; // this now points to the head of the list
        
        while(headPtr->type != NULL_TYPE)
        {
            assert(headPtr->type == CONS_TYPE);
            Value* next = nextVal(headPtr);
            printf("1\n");
            assert(headPtr->c.car->type == PTR_TYPE); // the car of the node must be a PTR_TYPE
            free(headPtr->c.car->p);
            free(headPtr->c.car);
            free(headPtr);
            headPtr = next;
        }
        free(headPtr);
        listHead.c.cdr = NULL;
    }
}

// Replacement for the C function "exit", that consists of two lines: it calls
// tfree before calling exit.
void texit(int status){
    tfree();
    exit(status);
}