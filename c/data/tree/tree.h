#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

#define LEFT_NODE 0
#define RIGHT_NODE 1

typedef struct tree_node{
    struct tree_node *children;
    char val;
    int32_t num_children;
} tree_node;


typedef struct Tree{
    struct tree_node *head;
} Tree;

void dfs(Tree* tree){
    tree_node *cur = (tree_node*)malloc(sizeof(tree_node));
    Vec stack = {7, 0, (char*)malloc(sizeof(tree_node) * 7), sizeof(tree_node)};
    vec_append(&stack, tree->head);
    while (!vec_is_empty(&stack)){
        vec_pop(&stack, cur);
        printf("%d\n", cur->val);
        for (int i = 0; i < cur->num_children; ++i){
            vec_append(&stack, &cur->children[i]);
        }
    }
}
