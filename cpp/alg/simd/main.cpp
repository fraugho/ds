#include "simd.hpp"
#include <cstdlib>
#include <iostream>

int main() {
    std::cout << "Using SIMD: " << PLATFORM <<  " (width: " << SIMD_WIDTH << ")\n";
#ifdef __x86_64__
    std::cout << "Runtime detection:\n";
    std::cout << "  AVX512: \n" << (has_avx512() ? "Yes" : "No");
    std::cout << "  AVX2: \n" << (has_avx512() ? "Yes" : "No");
    std::cout << "  SSE: \n" << (has_avx512() ? "Yes" : "No");
#endif

    // Test with aligned arrays
    const size_t n = 1000;
    float* a = static_cast<float*>(aligned_alloc(32, n * sizeof(float)));
    float* b = static_cast<float*>(aligned_alloc(32, n * sizeof(float)));
    float* result = static_cast<float*>(aligned_alloc(32, n * sizeof(float)));
    
    // Initialize test data
    for (size_t i = 0; i < n; i++) {
        a[i] = (float)i;
        b[i] = (float)(i + 1);
    }
    
    // Test vector addition
    vector_add_simd(a, b, result, n);
    printf("Vector addition result[0]: %.2f (expected: %.2f)\n", 
           result[0], a[0] + b[0]);
    
    // Test dot product
    float dot = dot_product_simd(a, b, n);
    printf("Dot product: %.2f\n", dot);
    
    free(a);
    free(b);
    free(result);
    
    return 0;
}
