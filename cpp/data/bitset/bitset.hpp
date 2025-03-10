#ifndef BITSET_H
#define BITSET_H

#include <iostream>
#include <stdint.h>

template <size_t size>
class BitSet{
    public:
        BitSet(){


        }

        void print(){
            int data_len = size / 8;
            int times = 0;
            uint8_t mask = 0x80;
            for(int i = 0; i < data_len; ++i){
                for(int j = 0; j < 8; ++j, data[i] << 1, ++times){
                    std::cout << data[i] & mask ? 1 : 0;
                    if (times == size - 1){
                        return;
                    }
                }
            }
            int i = 0;
            while(i < size){

            }
        }
    private:
        uint8_t data[(size / 8) + 1];
};

#endif
