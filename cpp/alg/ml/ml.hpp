#ifndef ML_HPP
#define ML_HPP


#include <iostream>
#include <vector>
#include <math.h>

enum ActivationFunctions{
    Sigmoid,
    Linear,
    Tanh,
    Softmax,
    ReLU
};

struct Neuron{
    float weight;
    float bias;
    ActivationFunctions fn;
};

void to_do(){
    std::cout << "you forgot to implement to do\n";
    exit(1);
}

#define DEFAULT_NEURON {1,1, Linear}

class NN{
    public:
        const double EULER = 2.71828182845904523536;
        std::vector<std::vector<Neuron>> layers;
        int input_l, output_l;

        NN(int input, int output){
            input_l = input;
            output_l = output;
        }

        void fc(int layer, int width){
            layers.push_back({DEFAULT_NEURON});
        }

        std::vector<float> ff(std::vector<float> inputs){
            int i;
            float result = 0;
            for(auto layer : layers){
                int size = inputs.size();
                for(auto neuron : layer){
                    for(i = 0; i < size; ++i){
                        result += inputs[i] * neuron.weight + neuron.bias;
                    }
                    inputs.push_back(apply_activation_fn(result, neuron.fn));
                    result = 0;
                }
            }
            return inputs;
        }

        std::vector<float> rnff(std::vector<float> inputs){
            std::vector<float> result;
            float r = 0;
            for(auto layer : layers){
                for(auto neuron : layer){
                    for(auto input : inputs){
                        r += input * neuron.weight + neuron.bias;
                    }
                    result.push_back(apply_activation_fn(r, neuron.fn));
                    r = 0;
                }
                inputs.swap(result);
                result.clear();
            }
            return inputs;
        }

    private:
        inline float apply_activation_fn(float input, ActivationFunctions fn){
            switch(fn){
                case Linear:
                    return input;
                case ReLU:
                    return (input > 0) ? input : 0;
                case Tanh:
                    return std::tanh(input);
                case Sigmoid:
                    return 1 / (1 + pow(EULER, input));
                case Softmax:
                    to_do();
            }
            return 0;
        }
};
#endif
