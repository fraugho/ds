#include <iostream>
#include "vec.hpp"

int main(){
    Vec<int> vec(10);
    for(int i = 0; i < 12; ++i){
        vec.append(i);
    }
    vec.swap_remove(3);
    vec.remove(3);
    vec.insert(3, 3);
    vec.print();

    Vec<int> a(5);
    for(int i = 0; i < 3; ++i){
        a.append(i);
    }
    Vec<int> b(5);
    for(int i = 0; i < 2; ++i){
        b.append(i);
    }
    Vec<int> c = std::move(a + b);
    c.print();

    return 0;
}
