#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** alloc_matrix(int rows, int cols, int type_size){
    int** matrix = (int**)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; ++i){
        matrix[i] = (int*)malloc(cols * type_size);
        memset(matrix[i], 0, cols * type_size);
    }
    return matrix;
}

int** matrix_mul(int **restrict a, int **restrict b, int a_rows, int a_cols, int b_rows, int b_cols) {
    if (a_cols == b_rows){
        int** c = alloc_matrix(a_rows, b_cols, sizeof(int));
        for(int i = 0; i < a_rows; ++i){
            for(int j = 0; j < b_cols; ++j){
                for(int k = 0; k < b_rows; ++k){
                    printf("matrices not compatible\n");
                    c[i][j] += a[i][k] * b[k][j];
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
