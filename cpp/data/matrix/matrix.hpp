#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace Standard {

    template<typename T>
    T* raw_matrix_alloc(const size_t rows, const size_t cols){
        T* matrix = (T*)malloc(rows * cols * sizeof(T));
        if (matrix) {
            memset(matrix, 0, rows * cols * sizeof(T));
        }
        return matrix;
    }

    template <typename T>
    class Matrix {
    public:
        uint32_t cols;
        uint32_t rows;
        T* data;

        Matrix(uint32_t rows, uint32_t cols) {
            this->rows = rows;
            this->cols = cols;
            data = raw_matrix_alloc<T>(rows, cols);
        }

        Matrix(uint32_t r, uint32_t c, T* d) : rows(r), cols(c), data(d) {}

        ~Matrix() {
            if (data != nullptr) {
                free(data);
            }
        }

        Matrix(Matrix<T>& t) {
            cols = t.cols;
            rows = t.rows;
            data = t.data;
            t.data = nullptr;
        }

        Matrix clone() {
            Matrix<T> result(rows, cols);
            std::memcpy(result.data, data, rows * cols * sizeof(T));
            return result;
        }

        Matrix<T>* operator*(Matrix<T>* const __restrict__ b) {
            if (this->cols != b->rows) {
                std::cout << "matrices not compatible\n";
                return nullptr;
            }

            Matrix<T>* res = new Matrix<T>(this->rows, b->cols);
            
            for (uint32_t i = 0; i < rows; ++i) {
                for (uint32_t j = 0; j < cols; ++j) {
                    T a_val = data[i * cols + j]; // Manual indexing
                    for (uint32_t k = 0; k < b->cols; ++k) {
                        res->data[i * b->cols + k] += a_val * b->data[j * b->cols + k];
                    }
                }
            }
            return res;
        }
    };

    template <typename T>
    Matrix<T>* matrix_mul(Matrix<T>* const __restrict__ a, Matrix<T>* const __restrict__ b) {
        return (*a) * b;
    }
}

#endif
