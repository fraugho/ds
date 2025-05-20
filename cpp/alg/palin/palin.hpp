#ifndef PALIN_HPP
#define PALIN_HPP
#include <emmintrin.h>
#include <iostream>
#include <cstring>
//#include <immintrin.h>
#include <smmintrin.h>

[[nodiscard]] bool palindrome(std::string& s){
    size_t len = s.length();
    std::cout << "len: " << len << "\n";
    for(int i = 0; i < len / 2; ++i){
        if (s[i] != s[len - (i + 1)]){
            return false;
        }
    }
    return true;
}

char* reverse_string(std::string& s){
    int len = s.length();
    char* rev = new char[len];
    for(int i = 0; i < len; ++i){
        rev[i] = s[len - (i + 1)];
    }
    std::cout << rev << "\n";
    return rev;
}

[[nodiscard]] bool simd_palindrome(std::string& s){
    char a[16] = {0};
    char b[16] = {0};
    int len = s.length();

    memcpy(a, &s[0], len);

    char* rev = reverse_string(s);
    memcpy(b, rev, len);

    __m128i x =_mm_setzero_si128();
    memcpy(&x, a, 16);

    __m128i y = _mm_setzero_si128();
    memcpy(&y,  b, 16);

    __m128i result = _mm_sub_epi8(x, y);

    return _mm_testz_si128(result, result);
}

#endif
