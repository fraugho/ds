#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** matrix_alloc(int rows, int cols, int type_size){
    int** matrix = (int**)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; ++i){
        matrix[i] = (int*)malloc(cols * type_size);
        memset(matrix[i], 0, cols * type_size);
    }
    //printf("rows:%d cols:%d\n", rows, cols);
    return matrix;
}

int** matrix_dealloc(int** matrix, int rows, int cols){
    for(int i = 0; i < rows; ++i){
        free(matrix[i]);
    }
    return matrix;
}

int** matrix_mul(int **const restrict a, int ** const restrict b,
        const int a_rows, const int a_cols, const int b_rows, const int b_cols) {
    if (a_cols == b_rows){
        int** c = matrix_alloc(a_rows, b_cols, sizeof(int));
        for(int i = 0; i < a_rows; ++i){
            for(int j = 0; j < a_cols; ++j){
                for(int k = 0; k < b_cols; ++k){
                    c[i][k] += a[i][j] * b[j][k];
                }
            }
        }
        return c;
    }
    else {
        printf("matrices not compatible\n");
        return NULL;
    }
}

#endif // !DEBUG
