#ifndef ARENA_H
#define ARENA_H

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
    arena->data = (char*)malloc(cap);
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

#endif
