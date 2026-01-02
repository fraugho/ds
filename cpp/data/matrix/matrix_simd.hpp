#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <immintrin.h>
#include <type_traits>

namespace Simd {

    template<typename T>
    T* raw_matrix_alloc(const size_t rows, const size_t cols) {
        size_t size = rows * cols * sizeof(T);
        T* matrix = (T*)aligned_alloc(64, size); 
        if (matrix) std::memset(matrix, 0, size);
        return matrix;
    }

    template <typename T>
    class Matrix {
        static_assert(std::is_arithmetic<T>::value, "Matrix type must be numeric");
    public:
        uint32_t cols;
        uint32_t rows;
        T* data;

        Matrix(uint32_t rows, uint32_t cols) : rows(rows), cols(cols) {
            data = raw_matrix_alloc<T>(rows, cols);
        }

        ~Matrix() {
            if (data) free(data);
        }

        T& at(uint32_t r, uint32_t c) { return data[r * cols + c]; }

        Matrix<T>* operator*(Matrix<T>* const __restrict__ b) {
            if (cols != b->rows) return nullptr;

            Matrix<T>* res = new Matrix<T>(rows, b->cols);
            uint32_t B_cols = b->cols;

            for (uint32_t i = 0; i < rows; ++i) {
                for (uint32_t j = 0; j < cols; ++j) {
                    T a_val = data[i * cols + j];

                    uint32_t k = 0;
                    if constexpr (std::is_same_v<T, float>) {
                        __m512 a_vec = _mm512_set1_ps(a_val);
                        for (; k <= B_cols - 16; k += 16) {
                            __m512 b_vec = _mm512_loadu_ps(&b->data[j * B_cols + k]);
                            __m512 c_vec = _mm512_loadu_ps(&res->data[i * B_cols + k]);
                            
                            c_vec = _mm512_fmadd_ps(a_vec, b_vec, c_vec);
                            
                            _mm512_storeu_ps(&res->data[i * B_cols + k], c_vec);
                        }
                    } 
                    else if constexpr (std::is_same_v<T, double>) {
                        __m512d a_vec = _mm512_set1_pd(a_val);
                        for (; k <= B_cols - 8; k += 8) {
                            __m512d b_vec = _mm512_loadu_pd(&b->data[j * B_cols + k]);
                            __m512d c_vec = _mm512_loadu_pd(&res->data[i * B_cols + k]);
                            
                            c_vec = _mm512_fmadd_pd(a_vec, b_vec, c_vec);
                            
                            _mm512_storeu_pd(&res->data[i * B_cols + k], c_vec);
                        }
                    }

                    for (; k < B_cols; ++k) {
                        res->data[i * B_cols + k] += a_val * b->data[j * B_cols + k];
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
