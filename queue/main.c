#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue{
    int32_t capacity;
    int32_t used;
    char *data;
    char type_size;
} Queue;

void
queue_add(Queue *queue, void* thing){
    if (queue->used < queue->capacity){
        memcpy(&queue->data[(queue->capacity - queue->used - 1) * queue->type_size], thing, queue->type_size);
        ++queue->used;
    }
    else{
        queue->data = realloc(queue->data, queue->capacity * queue->type_size * 2);
        memcpy(&queue->data[queue->used * queue->type_size], thing, queue->type_size);
        ++queue->used;
        queue->capacity *= 2;
    }
}

void
queue_pop(Queue *queue, void* dest){
    if (queue->used | 0){
        memcpy(dest, &queue->data[queue->used-- * queue->type_size], queue->type_size);
    }
}

void
queue_insert(Queue *queue, void* thing, int32_t index){
    if (queue->used < queue->capacity){

        //moves data
        memcpy(&queue->data[(queue->capacity - (queue->used + 1)) * queue->type_size],
               &queue->data[(queue->capacity - (queue->used + 1)) * queue->type_size],
               queue->type_size *  (queue->used - index)
        );
        printf("hey: %d\n", queue->type_size *  (queue->used - index));
        printf("cap: %d\n", queue->capacity);
        //inserts data
        memcpy(&queue->data[(queue->capacity - (index + 1)) * queue->type_size], thing, queue->type_size);
        ++queue->used;
    }
    else{
        queue->data = realloc(queue->data, queue->capacity * queue->type_size * 2);
        memcpy(&queue->data[(index + 1) * queue->type_size], &queue->data[index * queue->type_size], queue->type_size *  (queue->used - index));
        memcpy(&queue->data[index * queue->type_size], thing, queue->type_size);
        ++queue->used;
        queue->capacity *= 2;
    }
}

void
queue_delete(Queue *queue, int32_t index){
    if (queue->used | 0){
        memcpy(&queue->data[index * queue->type_size], &queue->data[(index + 1) * queue->type_size], queue->type_size *  (queue->used-- - index));
    }
}

int
main(){
    int cap = 10;
    Queue queue = {cap, 0, malloc(cap * sizeof(int)), sizeof(int)};
    for (int i = 1; i < queue.capacity; ++i){
        queue_add(&queue, &i);
    }
    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + (queue.used - i)));
    }

    printf("pop\n");
    int pop;
    queue_pop(&queue, &pop);
    printf("val: %d\n", pop);

    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + (queue.used - i)));
    }


    printf("insert\n");

    int x = 44;
    queue_insert(&queue, &x, queue.used / 2);

    for (int i = 0; i < queue.used; ++i){
        printf("%d\n", *((int*)queue.data + (queue.used - i)));
    }

    /*
     *

    printf("delete\n");

    queue_delete(&vec,9);

    for (int i = 0; i < queue.capacity; ++i){
        printf("%d\n", *((int*)queue.data + i));
    }
     * */

    free(queue.data);
}

