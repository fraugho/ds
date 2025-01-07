#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue{
    int32_t capacity;
    int32_t used;
    char *data;
    char type_size;
} queue;

void
queue_append(queue *queue, void* thing){
    if (queue->used < queue->capacity){
        memcpy(&queue->data[queue->used * queue->type_size], thing, queue->type_size);
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
enqueue(queue *queue, void* thing){
    if (queue->used < queue->capacity){
        memcpy(&queue->data[queue->type_size], &queue->data[0], queue->type_size * queue->used++);
        memcpy(&queue->data[0], thing, queue->type_size);
    }
    else{
        queue->data = realloc(queue->data, queue->capacity * queue->type_size * 2);
        memcpy(&queue->data[queue->type_size], &queue->data[0], queue->type_size * queue->used++);
        memcpy(&queue->data[0], thing, queue->type_size);
        queue->capacity *= 2;
    }
}

void
queue_pop(queue *queue, void* dest){
    if (queue->used | 0){
        memcpy(dest, &queue->data[0], queue->type_size);
        memcpy(&queue->data[0], &queue->data[1 * queue->type_size], --queue->used * queue->type_size);
    }
}

void
queue_insert(queue *queue, void* thing, int32_t index){
    if (queue->used < queue->capacity){
        memcpy(&queue->data[(index + 1) * queue->type_size], &queue->data[index * queue->type_size], queue->type_size *  (queue->used - index));
        memcpy(&queue->data[index * queue->type_size], thing, queue->type_size);
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
queue_delete(queue *queue, int32_t index){
    if (queue->used | 0){
        memcpy(&queue->data[index * queue->type_size], &queue->data[(index + 1) * queue->type_size], queue->type_size *  (queue->used-- - index));
    }
}

int
main(){
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

