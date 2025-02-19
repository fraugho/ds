#include <iostream>
#include "palin.hpp"

int main(int argc, char** argv){
    std::string s;
    std::cout << "input string:\n";
    std::cin >> s;
    switch(simd_palindrome(s)){
        case true:
            std::cout << "Palindrome\n";
            break;
        case false:
            std::cout << "Not Palindrome\n";
            break;
    }
}

/*
    if (argv[1] != NULL){
        switch(palindrome(argv[1])){
            case true:
                std::cout << "Palindrome\n";
                break;
            case false:
                std::cout << "Not Palindrome\n";
                break;
        }
    } else {
        std::string s;
        std::cout << "input string:\n";
        std::cin >> s;
        switch(palindrome(s)){
            case true:
                std::cout << "Palindrome\n";
                break;
            case false:
                std::cout << "Not Palindrome\n";
                break;
        }
    }
 * */
