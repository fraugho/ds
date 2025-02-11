#include <iostream>
#include "strcmp.hpp"
#include <cstring>


int main(){
    const size_t len = 64 * 64 * 64 * 4;

    alignas(64) char a[len] = {'c'};
    a[1] = 'b';

    alignas(64) char b[len] = {'c'};

    size_t result = simd512_strcmp(a, b, len);

    if (result){
        std::cout << "true\n";
    } else {
        std::cout << "false\n";
    }

    std::cout <<  "result: " << result << "\n";

    return 0;
}
