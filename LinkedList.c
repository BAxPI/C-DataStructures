#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

typedef struct Node{
    struct Node *prev_node;
    struct Node *next_node;
    LItem node_content;
}Node; 


struct LList {
    Node *head; 
    Node *tail; 

    LItem (*ctor)(LItem);
    void (*dtor)(LItem);
    int (*compare)(LItem, LItem);  
    void (*print)(LItem);
};

LList new_linked_list(LItem (*ctor)(LItem),void (*dtor)(LItem), int (*compare)(LItem, LItem), void (*print)(LItem)){
    LList new_llist = calloc(1, sizeof(struct  LList));
    if (!new_llist){
        return NULL;
    }
    new_llist->head = NULL;
    new_llist->tail = NULL;
    // Functions provided by the client. 
    new_llist->ctor = ctor;
    new_llist->dtor = dtor;
    new_llist->compare = compare;
    new_llist->print = print;

    return new_llist;
}


void add_node(LList list, LItem item){
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;
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
}

/* Deletes first occurence of a node in a linked list */
void delete_node(LList list, LItem item){
    Node *ptr = list->head;
    while(ptr != NULL){
        if(list->compare(ptr->node_content, item) == 0){
            /* First node to be deleted */
            if(!ptr->prev_node){
                list->head = ptr->next_node;
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
            return;
        }
        ptr = ptr->next_node;
    }
}


void destroy_linked_list(LList list){
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
}

void print_list(LList list){
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
    printf("\033[0;31m"); /* Red */
    printf("NULL\n");
    printf("\033[0m"); /* Reset */
}