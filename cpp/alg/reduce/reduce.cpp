// C++ Program to implement calculate 
// the sum of the first n natural numbers 
// using Parallel Programming 
#include <chrono> 
#include <iostream>
#include <thread>
#include <immintrin.h>

uint64_t sum_serial(uint64_t n) 
{ 
    uint64_t sum = 0; 
    for (uint64_t i = 0; i < n; ++i) { 
        sum += i; 
    } 
    return sum; 
}

uint64_t simd_sum(uint64_t n) 
{ 
    uint64_t sum = 0; 
    __m512i x = _mm512_set_epi64(0, 1, 2, 3, 4, 5, 6, 7);
    __m512i y = _mm512_set1_epi64(8);

    for (uint64_t i = 0; i < n; i += 8) {
        sum += _mm512_reduce_add_epi64(x);
        x = _mm512_add_epi64(x, y);
    }

    return sum; 
}

// Parallel programming function 
uint64_t sum_parallel(uint64_t n) 
{ 
    uint64_t sum = 0; 
#pragma omp parallel for reduction(+ : sum) 
    for (uint64_t i = 0; i < n; ++i) { 
        sum += i; 
    } 
    return sum; 
}

typedef struct ThreadInfo{
    uint64_t work_num;
    int thread_num;
    uint64_t* result;
} ThreadInfo;

void thread_sum(const ThreadInfo ti){
    uint64_t start = ti.work_num * ti.thread_num;
    uint64_t end = start + ti.work_num;
    for (; start < end; ++start) { 
        ti.result[ti.thread_num] += start;
    }
    return;
}

uint64_t thread_par(uint64_t n) 
{ 
    int tc = 24;
    uint64_t sum = 0;
    uint64_t sumarr[24] = {0};
    std::thread threads[tc];
    for(int i = 0; i < tc; ++i){
        threads[i] = std::thread(thread_sum, ThreadInfo{n/tc, i, sumarr});
    }
    for(auto& thread : threads){
        thread.join();
    }
    for(int i = 0; i < tc; ++i){
        sum += sumarr[i];
    }
    return sum;
}

// Driver Function 
int main() 
{ 
    const uint64_t n = 64 * 64 * 64 * 4; 

    auto start_time = std::chrono::high_resolution_clock::now(); 
    uint64_t result_serial = sum_serial(n); 
    auto end_time = std::chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> serial_duration = end_time - start_time; 


    start_time = std::chrono::high_resolution_clock::now(); 
    uint64_t result_parallel = sum_parallel(n); 
    end_time = std::chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> parallel_duration  = end_time - start_time; 

    start_time = std::chrono::high_resolution_clock::now();
    uint64_t thread_result = thread_par(n);
    end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> thread_duration  = end_time - start_time; 
    
    start_time = std::chrono::high_resolution_clock::now();
    uint64_t simd_result = simd_sum(n);
    end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> simd_duration  = end_time - start_time; 

    std::cout << "Serial result: " << result_serial << "\n";
    std::cout << "Parallel result: " << result_parallel << "\n";
    std::cout << "Thread result: " << thread_result << "\n";
    std::cout << "Simd result: " << simd_result << "\n";

    std::cout << "Serial duration: " << serial_duration.count() << " seconds" << "\n"; 
    std::cout << "Parallel duration: "<< parallel_duration.count() << " seconds" << "\n"; 
    std::cout << "Thread duration: "<< thread_duration.count() << " seconds" << "\n"; 
    std::cout << "Simd duration: "<< simd_duration.count() << " seconds" << "\n"; 

    std::cout << "Speedup: " << serial_duration.count() / parallel_duration.count() << "\n"; 

    return 0; 
}
