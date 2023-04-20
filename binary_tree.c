#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>



typedef struct Node{
    struct Node *left;
    struct Node *right;
    struct Node *father;
    size_t n_hight;
    BTItem node_content;

}Node;


struct BT{
    Node *root;
    size_t No_elements;
    size_t hieght; 

    //Provided by the clinet
    BTItem (*ctor)(BTItem);
    void (*dtor)(BTItem);
    int (*compare)(BTItem, BTItem);
    void (*print)(BTItem);
};


BT new_binary_tree(BTItem (*ctor)(BTItem),void (*dtor)(BTItem), int (*compare)(BTItem, BTItem), void (*print)(BTItem)){
    BT binary_tree = calloc(1, sizeof(struct  BT));
    if (!binary_tree){
        return NULL;
    }
    // Default properties
    binary_tree->root = NULL;
    binary_tree->No_elements = 0;
    binary_tree->hieght = 0;

    // Provided by the client
    binary_tree->ctor = ctor;
    binary_tree->dtor = dtor;
    binary_tree->compare = compare;
    binary_tree->print = print;

    return binary_tree;
}


void add_node(BT binary_tree, CBTIem item){
    Node *new_node = (Node *)malloc(sizeof(Node));
    if(!new_node) return;


}

