#include <vec.hpp>
#include <iostream>

template <typename T>
class Tree{
    public:
        void init(){
            for(int i = 0; i < 7; ++i){
                head.append(i);
            }
        }
        void print(){
            Vec<int> queue;
            int vec_len = head.len();
                int index = 0;
            for(int i = 0;  i < vec_len; ++i){
                std::cout << head[index] << "\n";
                queue.append(2 * index + 1);
                queue.append(2 * index + 2);
                index = queue.pop_front();
            }
            return;
        }

    private:
        Vec<T> head;
        
};
