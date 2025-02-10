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

    for(int i = 0; i < len - 16; i+=16){
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

[[nodiscard]]
bool simd512_strcmp(char* a, char* b, size_t len){
    __m512i x;
    __m512i y;
    __mmask64 mask;
    //len % 64
    size_t remainder = len & 0x0000003F;

    for(int i = 0; i < len - 64; i += 64){
        x = _mm512_load_si512(&a[i]);
        y = _mm512_load_si512(&b[i]);

        mask = _mm512_cmpeq_epi8_mask(x, y);
        // If the mask is not all ones, it means there's a difference
        if (mask != 0xFFFFFFFFFFFFFFFF){
            return false;
        }
    }

    for(int i = 0; i < remainder; ++i){
        if (a[len - (i + 1)] != b[len - (i + 1)]){
            return false;
        }
    }

    return true;
}

bool duck(char* a, char* b, size_t len){
    __m512i x;
    __m512i y;
    __mmask64 mask;

    for(int i = 0; i < len; i += 64){
        size_t remaining = len - i;
        if (remaining < 64){
            // Handle remaining bytes
            for (size_t j = 0; j < remaining; j++){
                if (a[i + j] != b[i + j]){
                    return false;
                }
            }
            break;
        }

        x = _mm512_load_si512(&a[i]);
        y = _mm512_load_si512(&b[i]);

        mask = _mm512_cmpeq_epi8_mask(x, y);
        if (mask != 0xFFFFFFFFFFFFFFFF){
            // If the mask is not all ones, it means there's a difference
            for (int j = 0; j < 64; j++){
                if (a[i + j] != b[i + j]){
                    return false;
                }
            }
        }
    }

    return true;
}

void test(){
    alignas(64) char a[64];
    alignas(64) char b[64];

    __m512i x;
    __m512i y;

    x = _mm512_load_si512(&a[0]);
    y = _mm512_load_si512(&b[0]);
}

void test2(char* a, char* b){
    __m512i x;
    __m512i y;

    x = _mm512_load_si512(&a[0]);
    y = _mm512_load_si512(&b[0]);
}

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
