#include <iostream>
#include "simd.hpp"


int main(){
    int a[4] = { 1, 2, 3, 4};
    int b[4] = { 1, 2, 3, 4};

    int* c = simd_add(a, b);
    for(int i = 0; i < 4; ++i){
        std::cout << c[i] << "\n";
    }

    std::cout << "---------------------\n";
/*
    char x[16] = "abababababababa";
    char y[16] = "abababababababa";
 * */
    char x[8] = "racecar";
    char y[8] = "racecar";
    char* z = simd_sub(x, y);
    for(int i = 0; i < 16; ++i){
        std::cout << (int)z[i] << "\n";
    }
}
