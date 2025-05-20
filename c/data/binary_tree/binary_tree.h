#ifndef binary_tree_h
#define binary_tree_h

#include <stdio.h>
#include <stdlib.h>
#include "vec.h"
#include "int.h"

#define LEFT_NODE 0
#define RIGHT_NODE 1

typedef struct tree_node{
    char val;
} tree_node;

typedef struct BinaryTree{
    tree_node* head;
} BinaryTree;

BinaryTree new_binary_tree(u64 height){   
    return BinaryTree{(tree_node*)malloc(sizeof(tree_node) * ((height * 2) + 1))};
}

void dfs(BinaryTree* tree){
    tree_node *cur = (tree_node*)malloc(sizeof(tree_node));
    Vec stack = {7, 0, (char*)malloc(sizeof(tree_node) * 7), sizeof(tree_node)};
    vec_append(&stack, tree->head);
    while (!vec_is_empty(&stack)){
        vec_pop(&stack, cur);
        printf("%d\n", cur->val);
        for (int i = 0; i < 2; ++i){
        }
    }
}

#endif
