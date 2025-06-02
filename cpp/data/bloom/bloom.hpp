#ifndef BLOOM_HPP
#define BLOOM_HPP

#include "int.hpp"
#include <stdint.h>
#include <array>

class BloomFilter{
    private:
        bool* data;
        i32 len;
    public:
        BloomFilter(i32 len){
            this->len = len;
            data = new bool[len];
        }
        ~BloomFilter(){
            delete data;
        }
        void insert(i32 num){
            for(i32 hash: hash(num)){
                data[hash] = true;
            }
        }
        std::array<i32, 3> hash(i32 num){
            return std::array<i32, 3> {(num * 123) % len , (num * 456) % len, (num * 789) % len};
        }
        bool is_there(i32 num){
            for(i32 hash: hash(num)){
                if (data[hash] != true){
                    return false;
                }
            }
            return true;
        }
};

#endif 
