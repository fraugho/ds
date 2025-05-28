#ifndef BITBLOOM_HPP
#define BITBLOOM_HPP

#include "int.hpp"
#include <stdint.h>
#include <array>

class BloomFilter{
    private:
        u64* data;
        u64 len;
    public:
        BloomFilter(u64 l){
            len = l;
            data = new u64[(l / 64) + 1];
        }
        ~BloomFilter(){
            delete data;
        }
        void insert(u64 num){
            for(u64 hash: hash(num)){
                //it first gets which u64 hash bit is in then
                //does a mod 64 to turn hash bit position to binary
                data[hash / len] |= 0x8000000000000000 >> (hash & 0x3fffffffffffffff);
            }
        }
        std::array<u64, 3> hash(u64 num){
            return std::array<u64, 3> {(num * 123) % len , (num * 456) % len, (num * 789) % len};
        }
        bool is_there(u64 num){
            for(u64 hash: hash(num)){
                if (!(data[hash / len] & 0x8000000000000000 >> (hash & 0x3fffffffffffffff))){
                    return false;
                }
            }
            return true;
        }
};

#endif 
