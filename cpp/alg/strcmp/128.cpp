#include <iostream>
#include "strcmp.hpp"
#include <cstring>

int main(){
    const size_t len = 64 * 64 * 64 * 4;

    std::string a(len, 'c');
    a[1] = 'b';

    std::string b(len, 'c');

    std::cout << simd_strcmp(a, b) << "\n";
}
