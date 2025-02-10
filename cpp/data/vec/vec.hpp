#ifndef VEC_H
#define VEC_H

#include <cstdint>
#include <cstdlib>
#include <cstring>

template <typename T>
class Vec {
    private:
        T* data;
        uint32_t used;
        uint32_t cap;

    public:
        Vec(){
            data = new T[10];
            used = 0;
            cap = 10;
        }

        Vec(uint32_t size){
            data = new T[size];
            used = 0;
            cap = size;
        }

        ~Vec(){
            delete[] data;
        }

        T& operator[](uint32_t index){
            return data[index];
        }

        const T& operator[](uint32_t index) const {
            return data[index];
        }

        void append(T value){
            if(used < cap){
                data[used++] = value;
            } else{
                realloc(data, (cap * sizeof(T) * 2));
                data[used++] = value;
            }
        }

        void swap_remove(size_t index){
            data[index] = data[--used];
        }

        void remove(size_t index){
            std::memcpy(&data[index], &data[++index], (used-- - index) * sizeof(T));
        }

        void insert(size_t index, T value){
            memcpy(&data[index + 1], &data[index], (used++ - index) * sizeof(T));
            data[index] = value;
        }

        uint32_t get_end(){
            return used;
        }
};

#endif
