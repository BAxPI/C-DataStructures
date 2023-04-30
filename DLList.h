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
    Creates a new empty linked list 
    @param ctor Pointer to a constructor function for an element in the list. 
    @param dtor Pointer to a destructor function for an element in the list.
    @param compare Pointer to a comparison function between two elements in the list 
    @param print Pointer to a print function of an element in the list. 
    @return Pointer to an emty linked list 
*/
struct DLList *DLList_new(void * (*ctor)(void *),void (*dtor)(void *), int (*compare)(const void *, const void *), void (*print)(void *));

/* 
    Adds a node to the head of the list.
    @returns 1 if added successfuly 0 otherwise.
*/
int DLList_add(struct DLList *list, void * const item);

/*
    Deletes the first occurrence of an item in the list.
    @return 1 if deleted successfuly 0 otherwise.
*/
int DLList_delete(struct DLList *list, void * const item);

/* 
    Destroys a linked list and frees all the allocated memory. 
    @return 1 if destroyed successfuly 0 otherwise.
*/
int DLList_destroy(struct DLList *list);

/*
    Gets an element from the Linked List.
    @param success A pointer to int, will be set to 1 upon sucess 0 otherwise.
*/
void * DLList_get_item(const struct DLList *list, void * const element, int *success);

/*
    Gets the number of elements in the linked list.
*/
size_t DLList_No_items(const struct DLList * const list);

/*
    Prints the linked list (if given a print function to print a single element!)
*/
void DLList_print(const struct DLList * const list);


#endif


