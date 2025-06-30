#ifndef SIMD_H
#define SIMD_H
#include <stdio.h>
#include <stdlib.h>

// Platform detection and SIMD headers
#if defined(__aarch64__)
    #include <arm_neon.h>
    #define SIMD_WIDTH 4
    typedef float32x4_t simd_float;
    #define PLATFORM "ARM NEON"
#elif defined(__AVX512F__)
    #include <immintrin.h>
    #define SIMD_WIDTH 16
    typedef __m512 simd_float;
    #define PLATFORM "AVX512"
#elif defined(__AVX2__) || defined(__AVX__)
    #include <immintrin.h>
    #define SIMD_WIDTH 8
    typedef __m256 simd_float;
    #define PLATFORM "AVX/AVX2"
#elif defined(__SSE__)
    #include <immintrin.h>
    #define SIMD_WIDTH 4
    typedef __m128 simd_float;
    #define PLATFORM "SSE"
#else
    #define SIMD_WIDTH 1
    typedef float simd_float;
    #define PLATFORM "Scalar fallback"
#endif

// Portable SIMD operations
static inline simd_float simd_load(const float* ptr) {
#if defined(__aarch64__)
    return vld1q_f32(ptr);
#elif defined(__AVX512F__)
    return _mm512_load_ps(ptr);
#elif defined(__AVX2__) || defined(__AVX__)
    return _mm256_load_ps(ptr);
#elif defined(__SSE__)
    return _mm_load_ps(ptr);
#else
    return *ptr;
#endif
}

static inline void simd_store(float* ptr, simd_float vec) {
#if defined(__aarch64__)
    vst1q_f32(ptr, vec);
#elif defined(__AVX512F__)
    _mm512_store_ps(ptr, vec);
#elif defined(__AVX2__) || defined(__AVX__)
    _mm256_store_ps(ptr, vec);
#elif defined(__SSE__)
    _mm_store_ps(ptr, vec);
#else
    *ptr = vec;
#endif
}

static inline simd_float simd_add(simd_float a, simd_float b) {
#if defined(__aarch64__)
    return vaddq_f32(a, b);
#elif defined(__AVX512F__)
    return _mm512_add_ps(a, b);
#elif defined(__AVX2__) || defined(__AVX__)
    return _mm256_add_ps(a, b);
#elif defined(__SSE__)
    return _mm_add_ps(a, b);
#else
    return a + b;
#endif
}

static inline simd_float simd_mul(simd_float a, simd_float b) {
#if defined(__aarch64__)
    return vmulq_f32(a, b);
#elif defined(__AVX512F__)
    return _mm512_mul_ps(a, b);
#elif defined(__AVX2__) || defined(__AVX__)
    return _mm256_mul_ps(a, b);
#elif defined(__SSE__)
    return _mm_mul_ps(a, b);
#else
    return a * b;
#endif
}

static inline simd_float simd_set1(float value) {
#if defined(__aarch64__)
    return vdupq_n_f32(value);
#elif defined(__AVX512F__)
    return _mm512_set1_ps(value);
#elif defined(__AVX2__) || defined(__AVX__)
    return _mm256_set1_ps(value);
#elif defined(__SSE__)
    return _mm_set1_ps(value);
#else
    return value;
#endif
}

// Example: Vector addition with SIMD
void vector_add_simd(const float* a, const float* b, float* result, size_t length) {
    size_t simd_end = (length / SIMD_WIDTH) * SIMD_WIDTH;
    
    // SIMD loop
    for (size_t i = 0; i < simd_end; i += SIMD_WIDTH) {
        simd_float vec_a = simd_load(&a[i]);
        simd_float vec_b = simd_load(&b[i]);
        simd_float vec_result = simd_add(vec_a, vec_b);
        simd_store(&result[i], vec_result);
    }
    
    // Handle remaining elements
    for (size_t i = simd_end; i < length; i++) {
        result[i] = a[i] + b[i];
    }
}

// Example: Dot product with SIMD
float dot_product_simd(const float* a, const float* b, size_t length) {
    simd_float sum_vec = simd_set1(0.0f);
    size_t simd_end = (length / SIMD_WIDTH) * SIMD_WIDTH;
    
    // SIMD loop
    for (size_t i = 0; i < simd_end; i += SIMD_WIDTH) {
        simd_float vec_a = simd_load(&a[i]);
        simd_float vec_b = simd_load(&b[i]);
        simd_float product = simd_mul(vec_a, vec_b);
        sum_vec = simd_add(sum_vec, product);
    }
    
    // Extract sum from SIMD register
    float sum = 0.0f;
#if defined(__aarch64__)
    float32x2_t low = vget_low_f32(sum_vec);
    float32x2_t high = vget_high_f32(sum_vec);
    float32x2_t sum_pair = vadd_f32(low, high);
    sum = vget_lane_f32(vpadd_f32(sum_pair, sum_pair), 0);
#elif defined(__AVX512F__)
    sum = _mm512_reduce_add_ps(sum_vec);
#elif defined(__AVX2__) || defined(__AVX__)
    __m128 low = _mm256_castps256_ps128(sum_vec);
    __m128 high = _mm256_extractf128_ps(sum_vec, 1);
    __m128 sum128 = _mm_add_ps(low, high);
    sum128 = _mm_hadd_ps(sum128, sum128);
    sum128 = _mm_hadd_ps(sum128, sum128);
    sum = _mm_cvtss_f32(sum128);
#elif defined(__SSE__)
    __m128 shuf = _mm_shuffle_ps(sum_vec, sum_vec, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _mm_add_ps(sum_vec, shuf);
    shuf = _mm_movehl_ps(shuf, sums);
    sums = _mm_add_ss(sums, shuf);
    sum = _mm_cvtss_f32(sums);
#else
    sum = sum_vec;
#endif
    
    // Handle remaining elements
    for (size_t i = simd_end; i < length; i++) {
        sum += a[i] * b[i];
    }
    
    return sum;
}

// Runtime feature detection (x86 only)
#ifdef __x86_64__
#include <cpuid.h>

int has_avx512() {
    unsigned int eax, ebx, ecx, edx;
    return __get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx) && (ebx & bit_AVX512F);
}

int has_avx2() {
    unsigned int eax, ebx, ecx, edx;
    return __get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx) && (ebx & bit_AVX2);
}

int has_sse() {
    unsigned int eax, ebx, ecx, edx;
    return __get_cpuid(1, &eax, &ebx, &ecx, &edx) && (edx & bit_SSE);
}
#endif
#endif
