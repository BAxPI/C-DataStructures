/* 
    Implements doubly linked list.

    ----------          ----------           ---------- 
    |  HEAD  | <------> |  NODE  | <------>  |  TAIL  | 
    ----------          ----------           ---------- 
    The linked list is generic and may hold any kind of pointer (from the same type!) given a proper constructor function for that type.

    Created by: @BAxBI as part of General DataStructure library for C.
 
*/
#ifndef __DLLIST__H_
#define __DLLIST__H_
#include <stddef.h>


typedef enum {false = 0, true = 1} bool;

/*
    @brief Linked List type.
*/
// typedef struct DLList * DLList;


/* 
    Creates a new empty linked list 
    @param ctor Pointer to a constructor function for an element in the list. 
    @param dtor Pointer to a destructor function for an element in the list.
    @param compare Pointer to a comparison function between two elements in the list 
    @param print Pointer to a print function of an element in the list. 
    @return Pointer to an emty linked list 
*/
struct DLList *DLList_new(void * (*ctor)(void *),void (*dtor)(void *), int (*compare)(void *, void *), void (*print)(void *));

/* 
    Adds a node to the head of the list.
    @param list The list to add the element to. 
    @param item A pointer to the item to add to the list.     
*/
int DLList_add(struct DLList *list, void * const item);

/*
    Deletes the first occurrence of an item in the list.
    @param list The list to delete the item from. 
    @param item The item to delete. 
*/
int DLList_delete(struct DLList *list, void * const item);

/* 
    Destroys a linked list and frees all the allocated memory. 
    @param list The linked list to destroy. 
*/
int DLList_destroy(struct DLList *list);

/*
    Gets an element from the Linked List.
    @param list The list to get the element from.
    @param element The element to get from the list.
    @return The element from the list if exist NULL otherwise
*/
void * DLList_get_item(const struct DLList *list, void * const element);

/*
    Gets the number of elements in the linked list.
    @param list The list the check its number of elements.
    @return The number of elements in the linked list.
*/
size_t DLList_No_items(const struct DLList * const list);

/*
    Prints the linked list (if given a print function to print a single element!)
    @param list The linked list to be printed.
*/
void DLList_print(const struct DLList * const list);


#endif


