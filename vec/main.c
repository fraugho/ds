#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vec{
    int32_t capacity;
    int32_t used;
    char *data;
    char type_size;
} Vec;

void
vec_append(Vec *vec, void* thing){
    if (vec->used < vec->capacity){
        memcpy(&vec->data[vec->used * vec->type_size], thing, vec->type_size);
        ++vec->used;
    }
    else{
        vec->data = realloc(vec->data, vec->capacity * vec->type_size * 2);
        memcpy(&vec->data[vec->used * vec->type_size], thing, vec->type_size);
        ++vec->used;
        vec->capacity *= 2;
    }
}

void
vec_pop(Vec *vec, void* dest){
    if (vec->used | 0){
        memcpy(dest, &vec->data[--vec->used * vec->type_size], vec->type_size);
    }
}

void
vec_insert(Vec *vec, void* thing, int32_t index){
    if (vec->used < vec->capacity){
        memcpy(&vec->data[(index + 1) * vec->type_size], &vec->data[index * vec->type_size], vec->type_size *  (vec->used - index));
        memcpy(&vec->data[index * vec->type_size], thing, vec->type_size);
        ++vec->used;
    }
    else{
        vec->data = realloc(vec->data, vec->capacity * vec->type_size * 2);
        memcpy(&vec->data[(index + 1) * vec->type_size], &vec->data[index * vec->type_size], vec->type_size *  (vec->used - index));
        memcpy(&vec->data[index * vec->type_size], thing, vec->type_size);
        ++vec->used;
        vec->capacity *= 2;
    }
}

void
vec_delete(Vec *vec, int32_t index){
    if (vec->used | 0){
        memcpy(&vec->data[index * vec->type_size], &vec->data[(index + 1) * vec->type_size], vec->type_size *  (vec->used-- - index));
    }
}

int
main(){
    int cap = 10;
    Vec vec = {cap, 0, malloc(cap * sizeof(int)), sizeof(int)};
    for (int i = 0; i < vec.capacity; ++i){
        vec_append(&vec, &i);
    }
    for (int i = 0; i < vec.capacity; ++i){
        printf("%d\n", *((int*)vec.data + i));
    }

    printf("append\n");
    for (int i = cap; i < cap + cap - 1; ++i){
        vec_append(&vec, &i);
    }
    for (int i = 0; i < vec.capacity; ++i){
        printf("%d\n", *((int*)vec.data + i));
    }

    printf("insert\n");

    int x = 44;
    vec_insert(&vec, &x, 9);

    for (int i = 0; i < vec.capacity; ++i){
        printf("%d\n", *((int*)vec.data + i));
    }

    printf("delete\n");

    vec_delete(&vec,9);

    for (int i = 0; i < vec.capacity; ++i){
        printf("%d\n", *((int*)vec.data + i));
    }

    free(vec.data);
}
