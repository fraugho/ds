#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

template<typename T>
T** raw_matrix_alloc(const size_t rows, const size_t cols){
    T** matrix = (int**)malloc(rows * sizeof(T *));
    for(int i = 0; i < rows; ++i){
        matrix[i] = (T*)malloc(cols * sizeof(T));
        memset(matrix[i], 0, cols * sizeof(T));
    }
    return matrix;
}

template <typename T>
class Matrix{
    public:
        uint32_t cols;
        uint32_t rows;
        T** data;

        Matrix(uint32_t r, uint32_t c){
            rows = r;
            cols = c;
            data = raw_matrix_alloc<T>(rows, cols);
        };

        ~Matrix(){
            for(size_t i = 0; i < rows; ++i){
                delete[] data[i];
            }
        }

        void print_matrix(){
            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j){
                    std::cout << data[i][j] << "\t";
                }
                std::cout << "\n";
            }
        }
};

template<typename T>
Matrix<T>* matrix_alloc(uint32_t rows, uint32_t cols){
    Matrix<T>* matrix = new Matrix<T>(rows, cols);
    matrix->data = raw_matrix_alloc<T>(rows, cols);
    return matrix;
}

template <typename T>
Matrix<T>* matrix_mul(Matrix<T>* __restrict__ a, Matrix<T>* __restrict__ b){
    if (a->cols == b->rows){
        Matrix<T>* c = matrix_alloc<T>(a->rows, b->cols);
        for(int i = 0; i < a->rows; ++i){
            for(int j = 0; j < a->cols; ++j){
                for(int k = 0; k < b->cols; ++k){
                    c->data[i][k] += a->data[i][j] * b->data[j][k];
                }
            }
        }
        return c;
    }
    else {
        std::cout << "matrices not compatible\n";
        return NULL;
    }
}

template <typename T>
T** raw_matrix_dealloc(T** matrix, size_t rows, size_t cols){
    for(size_t i = 0; i < rows; ++i){
        free(matrix[i]);
    }
    return matrix;
}

template<typename T>
T** raw_matrix_mul(const T **__restrict__ a, const int **__restrict__ b,
        const int a_rows, const size_t a_cols, const size_t b_rows, const int b_cols) {
    if (a_cols == b_rows){
        T** c = raw_matrix_alloc<T>(a_rows, b_cols);
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

#endif
