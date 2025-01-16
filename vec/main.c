#include <stdint.h>
#include <stdio.h>
#include <vec.h>

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
