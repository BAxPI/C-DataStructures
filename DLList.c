#include "DLList.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct Node{
    struct Node *prev_node;
    struct Node *next_node;
    void * node_content;
}Node; 


struct DLList {
    Node *head; 
    Node *tail; 
    size_t NoElements;
    // Functions provided by the client.
    void * (*ctor)(void *);
    void (*dtor)(void *);
    int (*compare)(void *, void *);  
    void (*print)(void *);
};


struct DLList *DLList_new(void * (*ctor)(void *),void (*dtor)(void *), int (*compare)(void *, void *), void (*print)(void *)){
    struct DLList *new_dllist = malloc(sizeof(*new_dllist));
    if (!new_dllist){
        return NULL;
    }
    new_dllist->head = NULL;
    new_dllist->tail = NULL;
    new_dllist->NoElements = 0;

    new_dllist->ctor = ctor;
    new_dllist->dtor = dtor;
    new_dllist->compare = compare;
    new_dllist->print = print;

    return new_dllist;
}


int DLList_add(struct DLList *list, void * const item){
    if(!list->ctor) return false; // If constructor is not provided.
    Node *new_node = malloc(sizeof(*new_node));
    if (!new_node) return false;
    new_node->next_node = NULL;
    new_node->prev_node = NULL;
    new_node->node_content = list->ctor(item);

    /* Empty list*/
    if(!list->head){
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        new_node->next_node = list->head;
        list->head->prev_node = new_node;
        list->head = new_node;
    }
    list->NoElements++;
    return true;
}

/* Deletes first occurence of a node in a linked list */
int DLList_delete(struct DLList *list, void * const item){
    Node *ptr = list->head;
    while(ptr != NULL){
        if(list->compare(ptr->node_content, item) == 0){
            /* First node to be deleted */
            if(!ptr->prev_node){
                list->head = ptr->next_node;
                if(ptr->next_node){
                    ptr->next_node->prev_node = NULL;
                }
            }
            else if(ptr->prev_node && ptr->next_node){
                ptr->next_node->prev_node = ptr->prev_node;
                ptr->prev_node->next_node = ptr->next_node;
            }
            else {
                ptr->prev_node->next_node = NULL;
            }
            if(list->dtor){
                list->dtor(ptr->node_content);
            }
            free(ptr);
            list->NoElements--;
            return true;
        }
        ptr = ptr->next_node;
    }
    return false;
}


int DLList_destroy(struct DLList * list){
    if(list){
    Node *ptr = list->head;
    while(ptr != NULL){
        Node *tmp = ptr;
        ptr = ptr->next_node;
        if(list->dtor){
            list->dtor(tmp->node_content);
        }
        free(tmp);
    }
    free(list);
    return true;
    }
    else{
        return true;
    }
}


void * DLList_get_item(const struct DLList *list, void * const element){
    Node *ptr = list->head;
    if(!list->head){
        printf("The list is empty!\n");
    }
    while(ptr!=NULL){
        if(list->compare(ptr->node_content, element) == 0){
            return ptr->node_content;
        }
        ptr = ptr->next_node;
    }
    printf("The element you're looking for is not in the linked list.\n");
    return NULL;
}

size_t DLList_No_items(const struct DLList *const list){
    return list->NoElements;
}


void DLList_print(const struct DLList * const list){
    if(!list->print) {
        printf("The linked list provided doesn't have print function\n");
        return;
    }
    if (!list->head) {
        printf("The list is empty!\n");
        return;
    }
    Node *ptr = list->head;
    while(ptr){
        list->print(ptr->node_content);
        if(ptr->next_node){
            printf(" <---> ");
        }
        else{
            printf(" ---> ");
        }
        ptr = ptr->next_node;
    }
    printf("NULL\n");
}
	
