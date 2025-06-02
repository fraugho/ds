#ifndef BITBLOOM_HPP
#define BITBLOOM_HPP

#include "int.hpp"
#include <stdint.h>
#include <array>

class BloomFilter{
    private:
        u8* data;
        u8 len;
    public:
        BloomFilter(u64 len){
            this->len = len;
            data = new u8[(len / 8) + 1];
        }
        ~BloomFilter(){
            delete data;
        }
        void insert(u64 num){
            for(u64 hash: hash(num)){
                //it first gets which u8 hash bit is in 
                //then a mod 8 to turn hash bit position in u8
                data[hash / 8] |= 0x80 >> (hash & 0x03);
            }
        }
        std::array<u64, 3> hash(u64 num){
            return std::array<u64, 3> {(num * 123) % len , (num * 456) % len, (num * 789) % len};
        }
        bool is_there(u64 num){
            for(u64 hash: hash(num)){
                if (!(data[hash / 8] & 0x80 >> (hash & 0x03))){
                    return false;
                }
            }
            return true;
        }
};

#endif 
