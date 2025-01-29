#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix{
    char** __restrict data;
    uint8_t width;
    uint8_t height;
} i8Matrix;

Matrix* matrix_mul(Matrix* __restrict a, Matrix* __restrict b, Matrix* __restrict c, uint8_t type){
    for(int i = 0; i < a->width; ++i){
        for(int j = 0; j < b->width; ++j){
            c->data[i * type][j * type] = a->data[i * type][j * type];
            //memcpy(c->data[i * type][j * type], );
        }
    }
}


#endif
