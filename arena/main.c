#include "arena.h"
#include <stdint.h>

typedef struct Monster{
    int32_t hp;
    int32_t atk;
} Monster;

void print_monster(Monster* m, uint32_t len){
    for(int i = 0; i < len; ++i){
        printf("Monster: %d, atk: %d, hp:%d\n", i, m[i].atk, m[i].hp);
    }
    printf("\n");
}

int main(){
    int num = 10;
    Arena* arena = arena_new(num * sizeof(Monster));
    Monster* m_1 = arena_alloc(arena, num * sizeof(Monster));
    for(int i = 0; i < num; ++i){
        m_1[i].atk = i;
        m_1[i].hp = i + 1;
    }

    print_monster(m_1, num);

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
}
