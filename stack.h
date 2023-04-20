/* 
    Implements a stack. 

    -----------
    |   TOP   |
    -----------
    -----------
    |  ITEM2  |
    -----------
    -----------
    |  ITEM3  |
    -----------
    The stack is generic and may hold any kind of data (from the same type!) given a proper constructor function for that type.

    =========== Usage ===========
    -- Defining a type that the stack will hold:  
        struct Vector3d {
            int x; int y; int z;
        }
    -- Constructor example: 
        SItem ctor(SItem item){
            struct Vector3d *vector = (struct Vector3d *)malloc(sizeof(struct Vector3d)); 
            memcpy(vector, item, sizeof(struct Vector3d));
            return vector;
        }
    -- Destructor example: 
        void dtor(SItem item){
            free(item);
        }
    -- Comparison example: 
        int compare(SItem item1, SItem item2){
            struct Vector3d *elem1 = (struct Vector3d *)item1;
            struct Vector3d *elem2 = (struct Vector3d *)item2;
            float size1 = sqrt(elem1->x + elem1->y + elem1->z);
            float size2 = sqrt(elem2->x + elem2->y + elem2->z);

            return (size1 > size2) - (size1 < size2); 
        }
    -- Printing example
        void print_vector3d(SItem item){
            printf("(%d, %d, %d)", ((struct Vector3d *)item)->x ,((struct Vector3d *)item)->y, ((struct Vector3d *)item)->z);
        }

    Created by: @BAxBI as part of General DataStructure library for C.
*/

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
