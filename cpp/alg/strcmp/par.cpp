#include <iostream>
#include <chrono>
#include <thread>

typedef struct ThreadInfo{
    size_t len;
    bool* same;
    char* __restrict__ a;
    char* __restrict__ b;
} ThreadInfo;

void thread_work(ThreadInfo ti){
    for(int i = 0; i < ti.len && *ti.same; ++i){
        if(ti.a[i] != ti.b[i]){
            *ti.same = false;
            return;
        }
    }
}

bool par_lin_strcmp(char* __restrict__ a, char* __restrict__ b, size_t len){
    bool same = true;
    int tc = 12;
    int i = 0;
    std::thread threads[tc];
    size_t size = len /12;
    for(i = 0; i < tc; ++i){
        threads[i] = std::thread(thread_work, ThreadInfo{size, &same, &a[size * i], &b[size * i]});
    }
    for(auto& thread: threads){
        thread.join();
    }
    return same;
}

int main(int argc, char** argv){
    const size_t len = 64 * 64 * 64 * 4;
    const int numIterations = std::stoi(argv[1]);

    alignas(64) char a[len] = {'c'};
    //a[1] = 'b';

    alignas(64) char b[len] = {'c'};

    // Warm-up iteration
    int temp = par_lin_strcmp(a, b, len);
    //int temp = lin_strcmp(a, b, len);

    uint64_t totalDuration = 0;
    size_t result = 0;
    for (int i = 0; i < numIterations; ++i) {
        auto start = std::chrono::steady_clock::now();
        //result = lin_strcmp(a, b, len);
        result = par_lin_strcmp(a, b, len);
        auto end = std::chrono::steady_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    double averageDuration = static_cast<double>(totalDuration) / numIterations;
    std::cout << "Average Duration: " << averageDuration << " ns\n";
    std::cout <<  "result: " << result << "\n";

    return 0;
}
