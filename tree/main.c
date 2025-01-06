#include <stdio.h>
#include <stdlib.h>
#include <vec.h>

typedef struct tree_node{
    struct tree_node *children;
    char val;
    int32_t num_children;
} tree_node;


typedef struct Tree{
    struct tree_node *head;
} Tree;

void
dfs(Tree* tree){
    tree_node *cur = malloc(sizeof(tree_node));
    Vec stack = {7, 0, malloc(sizeof(tree_node) * 7), sizeof(tree_node)};
    vec_append(&stack, tree->head);
    while (!vec_is_empty(&stack)){
        vec_pop(&stack, cur);
        printf("%d\n", cur->val);
        for (int i = 0; i < cur->num_children; ++i){
            vec_append(&stack, &cur->children[i]);
        }
    }
}

int
main(){
    tree_node *first = malloc(sizeof(struct tree_node));
    first->children = malloc(sizeof(struct tree_node) * 2);
    first->val = 1;
    first->num_children = 2;

    Tree tree = {first};

    first->children[0].val = 2;
    first->children[0].children = malloc(sizeof(struct tree_node) * 2);
    first->children[0].num_children = 2;


    first->children[0].children[0].val = 4;
    first->children[0].children[0].num_children = 0;

    first->children[0].children[1].val = 5;
    first->children[0].children[1].num_children = 0;

    first->children[1].val = 3;
    first->children[1].children = malloc(sizeof(struct tree_node) * 2);
    first->children[1].num_children = 2;

    first->children[1].children[0].val = 6;
    first->children[1].children[0].num_children = 0;

    first->children[1].children[1].val = 7;
    first->children[1].children[1].num_children = 0;

    dfs(&tree);
}

