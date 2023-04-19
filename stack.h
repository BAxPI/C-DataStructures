#ifndef __STACK__H_
#define __STACK__H_

#include <stdlib.h>
/*
    @brief Stack item.
*/
typedef void * SItem; // Represents an item in the stack.

/*
    @brief Constant stack item.
*/
typedef const void * CSItem; // Represents a constant item in the stack.

/*
    @brief Stack type.
*/
typedef struct Stack * Stack;

/* 
    Creates a new empty stack 
    @param ctor Pointer to a constructor function for an element in the stack. 
    @param dtor Pointer to a destructor function for an element in the stack.
    @param compare Pointer to a comparison function between two elements in the stack. 
    @param print Pointer to a print function of an element in the stack. 
    @return Pointer to an emty stack. 
*/
Stack new_stack(SItem (*ctor)(SItem),void (*dtor)(SItem), int (*compare)(SItem, SItem), void (*print)(SItem));

/*
    Gets the top item of the stack.
    @param stack The stack to get its top item.
    @return The top item in the stack.
*/
SItem top(Stack stack);

/*
    Removes the top item from the stack.
    @param stack The stack to remove its top item.
    @return The deleted item from the stack.
*/
SItem pop(Stack stack);

/*
    Adds a new item to the top of the stack.
    @param stack The stack to add the item to.
    @param s_item Stack item to add to the stack.
*/
void push(Stack stack, SItem s_item);

/*
    Gets the size of the stack (The number of elements in the stack).
    @param stack The stack to get its size.
    @return The size of the stack (0 if empty).
*/
size_t get_stack_size(Stack stack);

/* 
    Destroys a stack and frees all the allocated memory. 
    @param stack The stack to destroy. 
*/
void destroy_stack(Stack stack);

/*
    Prints the linked list (if given a print function to print a single element!)
    @param list The linked list to be printed.
*/
void print_stack(Stack stack);

#endif
