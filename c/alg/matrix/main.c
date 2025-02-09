#include "matrix.h"
#include <stdint.h>

typedef struct Matrix{
    uint32_t col;
    uint32_t row;
    void**restrict data;
    uint8_t data_type;
} Matrix;

int main(){
    int a_rows = 1, a_cols = 3;
    int** a = matrix_alloc(a_rows, a_cols, sizeof(int));

    int b_rows = 3, b_cols = 2;
    int** b = matrix_alloc(b_rows, b_cols, sizeof(int));

    for (int i = 0; i < a_rows; ++i){
        for (int j = 0; j < a_cols; ++j){
            a[i][j] = j + 1;
        }
    }

    for (int i = 0; i < b_cols; ++i){
        for (int j = 0; j < b_rows; ++j){
            b[j][i] = j + 1;
        }
    }

    int** c = matrix_mul(a, b, a_rows, a_cols, b_rows, b_cols);

    for (int i = 0; i < a_rows; ++i){
        printf("row: ");
        for (int j = 0; j < b_cols; ++j){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    matrix_dealloc(a, a_rows, a_cols);
    matrix_dealloc(b, b_rows, b_cols);
    matrix_dealloc(c, a_rows, b_cols);
}
