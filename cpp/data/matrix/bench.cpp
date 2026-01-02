#include <iostream>
#include <chrono>
#include <iomanip>
#include <typeinfo>
#include <cmath> // For std::abs

#include "matrix.hpp"
#include "matrix_simd.hpp"

using namespace std::chrono;

template <typename T>
void benchmark(uint32_t size) {
    std::cout << "\n--- Benchmarking " << typeid(T).name() << " | Size: " << size << "x" << size << " ---" << std::endl;

    // 1. Initialize Standard Matrices
    auto* A_std = new Standard::Matrix<T>(size, size);
    auto* B_std = new Standard::Matrix<T>(size, size);

    for(uint32_t i = 0; i < size; ++i) {
        for(uint32_t j = 0; j < size; ++j) {
            // Updated to 1D indexing
            A_std->data[i * size + j] = static_cast<T>(i + j);
            B_std->data[i * size + j] = static_cast<T>(i * j);
        }
    }

    // 2. Measure Standard Multiplication
    auto start_std = high_resolution_clock::now();
    auto* C_std = Standard::matrix_mul(A_std, B_std);
    auto end_std = high_resolution_clock::now();
    
    // 3. Initialize SIMD Matrices
    auto* A_simd = new Simd::Matrix<T>(size, size);
    auto* B_simd = new Simd::Matrix<T>(size, size);

    for(uint32_t i = 0; i < size; ++i) {
        for(uint32_t j = 0; j < size; ++j) {
            // Updated to 1D indexing
            A_simd->data[i * size + j] = static_cast<T>(i + j);
            B_simd->data[i * size + j] = static_cast<T>(i * j);
        }
    }

    // 4. Measure SIMD Multiplication
    auto start_simd = high_resolution_clock::now();
    auto* C_simd = Simd::matrix_mul(A_simd, B_simd);
    auto end_simd = high_resolution_clock::now();

    // 5. Verification: Check if results match
    bool match = true;
    for (uint32_t i = 0; i < size * size; ++i) {
        if (std::abs(C_std->data[i] - C_simd->data[i]) > 1e-4) {
            match = false;
            break;
        }
    }

    // Calculate Results
    auto d_std = duration_cast<microseconds>(end_std - start_std).count() / 1000.0;
    auto d_simd = duration_cast<microseconds>(end_simd - start_simd).count() / 1000.0;

    std::cout << "Result Match:  " << (match ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Standard Time: " << std::fixed << std::setprecision(3) << d_std << " ms" << std::endl;
    std::cout << "SIMD Time:     " << d_simd << " ms" << std::endl;
    std::cout << "Speedup:       " << (d_std / d_simd) << "x" << std::endl;

    // Cleanup
    delete A_std; delete B_std; delete C_std;
    delete A_simd; delete B_simd; delete C_simd;
}

int main() {
    // Note: Matrix size 256 is good, but SIMD thrives on sizes 
    // that are multiples of the vector width (16 for float, 8 for double).
    benchmark<float>(256);
    benchmark<double>(256);
    
    benchmark<float>(1024);
    
    return 0;
}
