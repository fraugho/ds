#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Arena{
    uint32_t used;
    uint32_t cap;
    char *data;
} Arena;

Arena* arena_new(uint32_t cap){
    struct Arena* arena =  (Arena*)malloc(sizeof(Arena));
    arena->data = (char*)malloc(cap);
    arena->used = 0;
    arena->cap = cap;
    return arena;
}

void* arena_alloc(Arena* arena, uint32_t size){
    if (arena->used + size > arena->cap)[[clang::unlikely]]{
        return NULL;
    }
    else{
        void *result = &arena->data[arena->used];
        arena->used += size;
        return result;
    }
}

static inline void free_arena(Arena* a){
    free(a->data);
    free(a);
}

typedef struct MPArena{
    uint32_t used;
    char *data;
} MPArena;

typedef struct MultiPool{
    MPArena* pools;
    uint32_t pool_cap;
    uint32_t cur_pool;
    uint32_t num_pool;
} MultiPool;

MultiPool* multi_pool_new(uint32_t pool_cap){
    MultiPool* multi_pool =  (MultiPool*)malloc(sizeof(MultiPool));

    multi_pool->pools = (MPArena*)malloc(sizeof(MPArena));
    multi_pool->pool_cap = pool_cap;
    multi_pool->cur_pool = 0;
    multi_pool->num_pool = 1;

    multi_pool->pools->used = 0;
    multi_pool->pools->data = (char*)malloc(pool_cap);
    return multi_pool;
}

void* mp_arena_alloc(MultiPool* mp, uint32_t size){
    if (mp->pools[mp->cur_pool].used + size > mp->pool_cap){
        mp->pools = (MPArena*)realloc(mp->pools, sizeof(MPArena) * mp->num_pool++ * 2);

        void *result = &mp->pools[mp->cur_pool].data[mp->pools[mp->cur_pool].used];
        mp->pools[mp->cur_pool].used += size;
        return result;
    }
    else{
        void *result = &mp->pools[mp->cur_pool].data[mp->pools[mp->cur_pool].used];
        mp->pools[mp->cur_pool].used += size;
        return result;
    }
}

void free_pool(MultiPool* mp){
    for(int i = 0; i < mp->num_pool; ++i){
        free(mp->pools[i].data);
    }
    free(mp->pools);
}
#endif
