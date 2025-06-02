#ifndef BITSET_H
#define BITSET_H

#include "int.hpp"
#include <iostream>
#include <stdint.h>
#include <array>

class BitSet{
    private:
        u8* data;
        u8 len;
    public:
        BitSet(u8 len){
            this->len = len;
            data = new u8[(len / 64) + 1];
        }
        ~BitSet(){
            delete data;
        }
        void insert(u8 index){
            data[index / len] |= 0x80 >> (index & 0x3f);
        }
};

#endif
