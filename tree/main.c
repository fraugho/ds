#include <stdio.h>
#include <stdlib.h>

struct tree_node{
    struct tree_node *children;
    char val;
};


struct Tree{
    struct tree_node *head;
};

int
main(){
    struct tree_node *first = malloc(sizeof(struct tree_node));
    first->children = malloc(sizeof(struct tree_node) * 2);
    first->val = 1;

    struct Tree tree = {first};

    first->children[0].val = 2;
    first->children[0].children = malloc(sizeof(struct tree_node) * 2);

    first->children[0].children[0].val = 4;
    first->children[0].children[1].val = 5;


    first->children[1].val = 3;
    first->children[1].children = malloc(sizeof(struct tree_node) * 2);


    first->children[1].children[0].val = 6;
    first->children[1].children[1].val = 7;

    struct tree_node *cur = tree.head;
    while(cur != NULL){
        printf("%d\n", cur->val);
        for (int i = 0; i < 2; ++i){
            printf("%d\n", cur->children[i].val);
        }
    }
}
