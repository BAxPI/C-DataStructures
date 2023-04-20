#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// Defines an item in the stack.
typedef struct s_item{
    struct s_item *prev_item;
    SItem s_item_content;
}s_item;

// Defines a stack.
struct Stack{
    // Stack properties
    s_item *top;
    size_t No_elements;

    // Provided by the client 
    SItem (*ctor)(SItem);
    void (*dtor)(SItem);
    int (*compare)(SItem, SItem);
    void (*print)(SItem);
};


Stack new_stack(SItem (*ctor)(SItem), void (*dtor)(SItem), int (*compare)(SItem, SItem), void (*print)(SItem)){
    Stack stack = calloc(1,sizeof(struct Stack));
    if(!stack){
        return NULL;
    }
    // Default
    stack->top = NULL;
    stack->No_elements = 0;
    // Provided by the client 
    stack->ctor = ctor;
    stack->dtor = dtor;
    stack->compare = compare;
    stack->print = print;

    return stack;
}


SItem top(Stack stack){
    return stack->top;
}


SItem pop(Stack stack){
    SItem item; 
    item = stack->top;
    stack->top = stack->top->prev_item;
    stack->No_elements--;
    return item;
}


void push(Stack stack, SItem item){
    s_item *new_item = (s_item *)malloc(sizeof(s_item));
    if (!new_item) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    if(stack->ctor) new_item->s_item_content = stack->ctor(item);
    else  new_item->s_item_content = item;

    new_item->prev_item = stack->top;
    stack->top = new_item;
}


size_t get_stack_size(Stack stack){
    return stack->No_elements; 
}


void destroy_stack(Stack stack){
    s_item *ptr = stack->top;
    
    while(ptr){
        s_item *tmp = ptr;
        ptr = ptr->prev_item;
        if(stack->dtor){
            stack->dtor(tmp->s_item_content);
        }
        free(tmp);
    }
    free(stack);
}


void print_stack(Stack stack){
    if(!stack->print) {
        printf("The stack provided doesn't have print function\n");
        return;
    }
    if (!stack->top) {
        printf("The stack is empty!\n");
        return;
    }    s_item *ptr = stack->top;
    while(ptr){
        stack->print(ptr->s_item_content);
        printf(" ---> ");
        ptr = ptr->prev_item;
    }
    printf("\033[0;31m"); /* Red */
    printf("NULL\n");
    printf("\033[0m"); /* Reset */
}
