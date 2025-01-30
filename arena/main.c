#include "arena.h"
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef struct Monster{
    int32_t hp;
    int32_t atk;
    char* name;
} Monster;

void print_monster(Monster* m, uint32_t len){
    for(int i = 0; i < len; ++i){
        printf("Monster: %d, atk: %d, hp: %d, name: %s\n", i, m[i].atk, m[i].hp, m[i].name);
    }
    printf("\n");
}

void delete_monster(Monster* m){
    free(m->name);
    free(m);
}

void reg_allocate(uint8_t num){
    char name_len = 8;
    Monster* m = malloc(num * (sizeof(Monster) + name_len));
    for(int i = 0; i < num; ++i){
        m[i].atk = i;
        m[i].hp = i + 1;
        m[i].name = malloc(name_len);
        strcpy(m[i].name, "bob_mar");
    }

    print_monster(m, num);

    for(int i = 0; i < num; ++i){
        free(m[i].name);
    }
    free(m);
}

void arena_allocate(uint8_t num){
    char name_len = 8;
    Arena* a = arena_new(num * (sizeof(Monster) + name_len));
    Monster* m = arena_alloc(a, num * sizeof(Monster));

    for(int i = 0; i < num; ++i){
        m[i].atk = i;
        m[i].hp = i + 1;
        m[i].name = arena_alloc(a, name_len);
        strcpy(m[i].name, "bob_mar");
    }

    print_monster(m, num);

    free_arena(a);
}

void mp_allocate(uint8_t num){
    char name_len = 8;
    MultiPool* mp = multi_pool_new(num * (sizeof(Monster) + name_len));
    Monster* m = mp_arena_alloc(mp, num * sizeof(Monster));

    for(int i = 0; i < num; ++i){
        m[i].atk = i;
        m[i].hp = i + 1;
        m[i].name = mp_arena_alloc(mp, name_len);
        strcpy(m[i].name, "bob_mar");
    }

    print_monster(m, num);

    free_pool(mp);
}

int main(){
    reg_allocate(10);
    arena_allocate(10);
    mp_allocate(10);
}

/*  
    int num = 10;
    Arena* arena = arena_new(num * sizeof(Monster));
    Monster* m_1 = arena_alloc(arena, num * sizeof(Monster));
    for(int i = 0; i < num; ++i){
        m_1[i].atk = i;
        m_1[i].hp = i + 1;
    }

    print_monster(m_1, num);

    free(arena);

    MultiPool* mp = multi_pool_new(num * sizeof(Monster));
    Monster* m_2 = mp_arena_alloc(mp, num * sizeof(Monster));
    for(int i = 0; i < num; ++i){
        m_2[i].atk = i;
        m_2[i].hp = i + 1;
    }

    print_monster(m_2, num);

    Monster* m_3 = mp_arena_alloc(mp, num * sizeof(Monster));
    for(int i = 0; i < num; ++i){
        m_3[i].atk = i * 2;
        m_3[i].hp = (i + 1) * 2;
    }

    print_monster(m_3, num);
    free(mp);

*/
