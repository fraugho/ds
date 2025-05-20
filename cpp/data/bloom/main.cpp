#include <iostream>
#include "bloom.hpp"

int main(){
    BloomFilter bloom = BloomFilter(10);
    bloom.insert(1);
    bloom.insert(2);
    bloom.insert(3);

    std::cout << "is there 1: " << bloom.is_there(1) << "\n";
    std::cout << "is there 2: " << bloom.is_there(2) << "\n";
    std::cout << "is there 3: " << bloom.is_there(3) << "\n";
    std::cout << "is there 4: " << bloom.is_there(4) << "\n";
    std::cout << "is there 5: " << bloom.is_there(5) << "\n";
}
