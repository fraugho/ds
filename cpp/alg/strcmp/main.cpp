#include <iostream>
#include "strcmp.hpp"


int main(){
    const size_t len = 1024576;

    std::string a;
    a.reserve(len);

    std::string b;
    b.reserve(len);

    for (int i = 0; i < len; i+=16){
        a.append("cccccccccccccccc");
        b.append("cccccccccccccccc");
    }

    std::cout << simd_strcmp(a, b) << "\n";
}
