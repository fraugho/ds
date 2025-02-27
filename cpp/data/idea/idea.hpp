#ifndef IDEA_HPP
#define IDEA_HPP

#include <optional>

#define DEFAULT_SIZE 10

//insert array
template<typename T>
class Idea{
    public:
        Idea(){
            data = new std::optional<T>[DEFAULT_SIZE];
        }

        void insert(size_t index, T& val){
            if(!data[index + 1].has_value()){
                data[index + 1] = data[index];
                data[index] = val;
            }
            else if(!data[index - 1].has_value()){
                data[index - 1] = val;
            }
            else {

            }
        }
    private:
        std::optional<T>* data;
};

#endif
