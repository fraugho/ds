#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int main(){
    int cap = 10;
    queue queue = {cap, 0, malloc(cap * sizeof(int)), sizeof(int)};
    printf("append\n");
    for (int i = 0; i < queue.capacity - 1; ++i){
        queue_append(&queue, &i);
    }
    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + i));
    }

    printf("insert\n");

    int x = 44;
    queue_insert(&queue, &x, 5);

    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + i));
    }

    printf("delete\n");

    queue_delete(&queue,5);

    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + i));
    }

    printf("pop\n");

    int pop;
    queue_pop(&queue,&pop);
    printf("pop val: %d\n", pop);

    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + i));
    }

    printf("enqueue\n");
    for (int i = 0; i < cap; ++i){
        enqueue(&queue, &i);
    }
    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + i));
    }

    free(queue.data);
}

