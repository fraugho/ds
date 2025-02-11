#include <iostream>
#include <cstring>


int main(){
    //const size_t len = 1024576;
    const size_t len = 64 * 64 * 64 * 4;

    std::string a(len, 'c');
    a[1] = 'b';

    std::string b(len, 'c');

    //std::cout << strcmp(&a[0], &b[0]) << "\n";
    bool result = a == b;
    std::cout << result << "\n";
}
