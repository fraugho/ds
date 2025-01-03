#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vec{
    int32_t capacity;
    int32_t used;
    char *data;
    char type_size;
};

void
vec_append(struct Vec *vec, void* thing){
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

int
main(){
    int cap = 10;
    struct Vec vec = {cap, 0, malloc(cap * sizeof(int)), sizeof(int)};
    for (int i = 0; i < vec.capacity; ++i){
        vec_append(&vec, &i);
    }
    for (int i = 0; i < vec.capacity; ++i){
        printf("%d\n", *((int*)vec.data + i));
    }

    for (int i = cap; i < cap + cap; ++i){
        vec_append(&vec, &i);
    }
    printf("double\n");
    for (int i = 0; i < vec.capacity; ++i){
        printf("%d\n", *((int*)vec.data + i));
    }
    free(vec.data);
}
