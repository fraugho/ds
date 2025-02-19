#ifndef SIMD_HPP
#define SIMD_HPP
#include <emmintrin.h>
#include <smmintrin.h>
#include <iostream>

[[nodiscard]]
int* simd_add(int* __restrict__ a, int* __restrict__ b){
    __m128i x =  _mm_loadu_si128((__m128i*) a);
    __m128i y = _mm_loadu_si128((__m128i*) b);
    x = _mm_add_epi32(x, y);

    int* z =  new int[4];
    _mm_store_si128((__m128i *)z, x);

    return z;
}

[[nodiscard]]
char* simd_sub(char* __restrict__ a, char* __restrict__ b){
    __m128i x =  _mm_loadu_si128((__m128i*) a);
    __m128i y = _mm_loadu_si128((__m128i*) b);
    x = _mm_sub_epi8(x, y);

    char* z =  new char[16];
    _mm_store_si128((__m128i *)z, x);

    return z;
}

[[nodiscard]]
bool palidrome(char* __restrict__ a, char* __restrict__ b){
    __m128i x = _mm_loadu_si128((__m128i *) a);
    __m128i y = _mm_loadu_si128((__m128i *) b);


}

#endif
