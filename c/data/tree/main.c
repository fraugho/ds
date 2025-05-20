#include <stdlib.h>
#include "tree.h"


int main(){
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

