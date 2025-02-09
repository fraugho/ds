#include <stdint.h>
#include "arena.h"
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

void print_monster_r(Monster** m, uint32_t len){
    for(int i = 0; i < len; ++i){
        printf("Monster: %d, atk: %d, hp: %d, name: %s\n", i, m[i]->atk, m[i]->hp, m[i]->name);
    }
    printf("\n");
}

void change_name(Monster* m, uint32_t len){
    for(int i = 0; i < len; ++i){
        strcpy(m[i].name, "fun");
    }
}

void change_name_r(Monster** m, uint32_t len){
    for(int i = 0; i < len; ++i){
        strcpy(m[i]->name, "fun");
    }
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


    //print_monster(m, num);
    change_name(m, num);

    for(int i = 0; i < num; ++i){
        free(m[i].name);
    }
    free(m);
}
//non contiguous
void arena_allocate_nc(uint8_t num){
    char name_len = 8;
    Arena* a = arena_new(num * (sizeof(Monster) + name_len));
    Monster* m = arena_alloc(a, num * sizeof(Monster));

    for(int i = 0; i < num; ++i){
        m[i].atk = i;
        m[i].hp = i + 1;
        m[i].name = arena_alloc(a, name_len);
        strcpy(m[i].name, "bob_mar");
    }

    //print_monster(m, num);
    change_name(m, num);

    free_arena(a);
}

//contiguous
void arena_allocate_c(uint8_t num){
    char name_len = 8;
    Arena* a = arena_new(num * (sizeof(Monster) + name_len));
    Monster* m[num];
    for(int i = 0; i < num; ++i){
        m[i] = arena_alloc(a, sizeof(Monster));
        m[i]->name = arena_alloc(a, name_len);
    }

    for(int i = 0; i < num; ++i){
        m[i]->atk = i;
        m[i]->hp = i + 1;
        strcpy(m[i]->name, "bob_mar");
    }

    //print_monster_r(m, num);
    change_name_r(m, num);

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

    //print_monster(m, num);
    change_name(m, num);

    free_pool(mp);
}

void time_test(uint32_t times, uint32_t quant){
    clock_t start = 0;
    clock_t end = 0;
    clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;

    for(int i = 0; i < times; ++i){
        start = clock();
        reg_allocate(quant);
        end = clock();
        t1 += difftime(end, start);

        start = clock();
        arena_allocate_nc(quant);
        end = clock();
        t2 += difftime(end, start);
        
        start = clock();
        arena_allocate_c(quant);
        end = clock();
        t3 += difftime(end, start);

        start = clock();
        mp_allocate(quant);
        end = clock();
        t4 += difftime(end, start);
    }
    printf("reg time took: %lu\n", t1 / times);
    printf("arena time nc took: %lu\n", t2 / times);
    printf("arena time c took: %lu\n", t3 / times);
    printf("multipool time took: %lu\n", t4 / times);
}

int main(){
    time_test(100000, 100);
}
