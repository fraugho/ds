#ifndef STRCMP_HPP
#define STRCMP_HPP

#include <iostream>
#include <immintrin.h>

[[nodiscard]]
bool simd_strcmp(std::string a, std::string b){
    int len = a.length();

    if(len != b.length()){
        return false;
    }

    __m128i x;
    __m128i y;

    for(int i = 0; i < len; i+=16){
        x = _mm_load_si128((__m128i*) &a[i]);
        y = _mm_load_si128((__m128i*) &b[i]);

        y = _mm_sub_epi8(x, y);

        if (_mm_testz_si128(y, y) == 0){
            return false;
        }
    }

    int remainder = len % 16;
    for(int i = 0; i < remainder; ++i){
        if (a[len - (i + 1)] != b[len - (i + 1)]){
            return false;
        }
    }

    return true;
}

/*
[[nodiscard]]
bool simd512_strcmp(std::string a, std::string b){
    int len = a.length();

    if(len != b.length()){
        return false;
    }

    __m512i x;
    __m512i y;

    for(int i = 0; i < len; i+=64){
        x = _mm512_load_si512(&a[i]);
        y = _mm512_load_si512(&b[i]);

        y = _mm512_sub_epi8(x, y);

        if (_mm512_test_epi8_mask(x, y) == 0){
            return false;
        }
    }

    int remainder = len % 64;
    for(int i = 0; i < remainder; ++i){
        if (a[len - (i + 1)] != b[len - (i + 1)]){
            return false;
        }
    }

    return true;
}
 * */

[[nodiscard]]
bool strcmp(std::string a, std::string b){
    int len = a.length();
    for(int i = 0; i < len; ++i){
        if(a[i] != b[i]){
            return false;
        }
    }

    return true;
}
#endif
