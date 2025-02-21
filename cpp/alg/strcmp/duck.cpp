#include <iostream>
#include "strcmp.hpp"
#include <cstring>
#include <chrono>

int main(int argc, char** argv){
    const size_t len = 64 * 64 * 64 * 4;
    const int numIterations = std::stoi(argv[1]);

    alignas(64) char a[len] = {'c'};
    //a[1] = 'b';

    alignas(64) char b[len] = {'c'};

    // Warm-up iteration
    duck(a, b, len);

    uint64_t totalDuration = 0;
    size_t result = 0;
    for (int i = 0; i < numIterations; ++i) {
        auto start = std::chrono::steady_clock::now();
        result = duck(a, b, len);
        auto end = std::chrono::steady_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    double averageDuration = static_cast<double>(totalDuration) / numIterations;
    std::cout << "Average Duration: " << averageDuration << " ns\n";
    std::cout <<  "result: " << result << "\n";

    return 0;
}
