#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct i8Matrix{
    int8_t* __restrict data;
    uint8_t width;
    uint8_t height;
} i8Matrix;

typedef struct u8Matrix{
    int8_t* __restrict data;
    uint8_t width;
    uint8_t height;
} u8Matrix;

typedef struct i32Matrix{
    int32_t* __restrict data;
    uint8_t width;
    uint8_t height;
} i32Matrix;

typedef struct u32Matrix{
    uint32_t* __restrict data;
    uint8_t width;
    uint8_t height;
} u32Matrix;

int* array_i8_mul(int8_t*__restrict a, int8_t*__restrict b, uint8_t width, uint8_t height){


}

int* matrix_i8_mul(i8Matrix* a, i8Matrix* b){
    if (a->width == b->height){
        i8Matrix* c = (i8Matrix*)malloc(sizeof(i8Matrix));
        c->data = (int8_t*)malloc(sizeof(int8_t) * a->height * b->width);
        for(int i = 0; i < a->width; ++i){
            for(int j = 0; j < a->width; ++i){

            }
        }
    } else {

    }
}
int* matrix_u8_mul(int*__restrict a, int*__restrict b){

}
int* matrix_i16_mul(int*__restrict a, int*__restrict b){

}
int* matrix_u16_mul(int*__restrict a, int*__restrict b){

}
int* matrix_i32_mul(int*__restrict a, int*__restrict b){

}
int* matrix_u32_mul(int*__restrict a, int*__restrict b){

}
int* matrix_i64_mul(int*__restrict a, int*__restrict b){

}
int* matrix_u64_mul(int*__restrict a, int*__restrict b){

}

#endif
