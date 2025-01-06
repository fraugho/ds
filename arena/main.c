#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Arena{
    int32_t used;
    int32_t cap;
    char *data;
};

struct Arena* arena_new(int32_t cap){
    struct Arena* arena =  (struct Arena*)malloc(sizeof(struct Arena));
    arena->data = malloc(cap);
    arena->used = 0;
    arena->cap = cap;
    return arena;
}

void*
arena_alloc(struct Arena* arena, int32_t size){
    if (arena->used + size > arena->cap)[[clang::unlikely]]{
        return NULL;
    }
    else{
        void *result = &arena->data[arena->used];
        arena->used += size;
        return result;
    }
}

struct Monster{
    int32_t hp;
    int32_t atk;
};

int
main(){
    struct Arena* bowl = arena_new(sizeof(struct Monster) * 3);
    struct Monster* bill = (struct Monster*)arena_alloc(bowl, sizeof(struct Monster));
    bill->hp = 1;
    bill->atk = 2;
    struct Monster* max = (struct Monster*)arena_alloc(bowl, sizeof(struct Monster));
    max->hp = 3;
    max->atk = 4;
    struct Monster* lochness = (struct Monster*)arena_alloc(bowl, sizeof(struct Monster));
    lochness->hp = 5;
    lochness->atk = 6;

    printf("bill hp: %d atk: %d\n", bill->hp, bill->atk);
    printf("max hp: %d atk: %d\n", max->hp, max->atk);
    printf("lochness hp: %d atk: %d\n", lochness->hp, lochness->atk);

    free(bowl->data);
    free(bowl);
}
