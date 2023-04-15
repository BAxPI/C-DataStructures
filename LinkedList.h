/* 
    Implements doubly linked list.

    ----------          ----------           ---------- 
    |  HEAD  | <------> |  NODE  | <------>  |  TAIL  | 
    ----------          ----------           ---------- 
    The linked list is generic and may hold any kind of data (from the same type!) given a proper constructor function for that type.

    Created by: @BAxBI as part of General DataStructure library for C.
 
*/
#ifndef __LINKED__LIST_H_
#define __LINKED__LIST__H_

typedef void * LItem;

typedef struct LList * LList;

/* 
    Creates a new empty linked list 
    @param ctor Pointer to a constructor function for an element in the list. 
    @param dtor Pointer to a destructor function for an element in the list.
    @param compare Pointer to a comparison function between two elements in the list 
    @param print Pointer to a print function of an element in the list. 
    @return Pointer to an emty linked list 
*/
LList new_linked_list(LItem (*ctor)(LItem),void (*dtor)(LItem), int (*compare)(LItem, LItem), void (*print)(LItem));
/* 
    Adds a node to the head of the list.
    @param list The list to add the element to. 
    @param item A pointer to the item to add to the list.     
*/
void add_node(LList list, LItem item);
/*
    Deletes the first occurrence of an item in the list.
    @param list The list to delete the item from. 
    @param item The item to delete. 
*/
void delete_node(LList list, LItem item);
/* 
    Destroys a linked list and frees all the allocated memory. 
    @param list The linked list to destroy. 
*/
void destroy_linked_list(LList list);
/*
    Prints the linked list (if given a print function to print a single element!)
    @param list The linked list to be printed.
*/
void print_list(LList list);





#endif