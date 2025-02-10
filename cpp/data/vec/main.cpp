#include <iostream>
#include "vec.hpp"

int main(){
    Vec<int> vec(10);
    for(int i = 0; i < 10; ++i){
        vec.append(i);
    }
    vec.swap_remove(3);
    vec.remove(3);
    vec.insert(3, 3);
    for(int i = 0; i < vec.get_end(); ++i){
        std::cout << vec[i] << "\n";
    }
}
