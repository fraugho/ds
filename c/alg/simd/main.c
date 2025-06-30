#include <stdio.h>
#include <stdlib.h>
#include "simd.h"

int main() {
    printf("Using SIMD: %s (width: %d)\n", PLATFORM, SIMD_WIDTH);
    
#ifdef __x86_64__
    printf("Runtime detection:\n");
    printf("  AVX512: %s\n", has_avx512() ? "Yes" : "No");
    printf("  AVX2: %s\n", has_avx2() ? "Yes" : "No");
    printf("  SSE: %s\n", has_sse() ? "Yes" : "No");
#endif

    // Test with aligned arrays
    const size_t n = 1000;
    float* a = aligned_alloc(32, n * sizeof(float));
    float* b = aligned_alloc(32, n * sizeof(float));
    float* result = aligned_alloc(32, n * sizeof(float));
    
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
