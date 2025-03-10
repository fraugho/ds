#include <iostream>
#include <thread>
#include <stdlib.h>
#include <vector>
#include <random>
#include "vec.hpp"

#define not_in -1
#define in 0
#define found 1


bool RUNNING = true;
typedef struct ThreadInfo{
    int* arr;
    int start;
    int end;
    int key;
    int tn;
    int* f;
} ThreadInfo;

typedef struct Work{
    int start;
    int end;
    int* arr;
    int key;
    int result;
    bool* is_found;
} Work;

void swap(int* arr, int cur, int end);
void print_array(int* arr, int len);
void mswap(int* arr, Work w);
void thread_task(Work w, int* result, int tn);
bool mt_search(int* arr, int len, const int tc, int key);
void rand_arr(int* arr, int len, int uniqueValue);

int main(){
int arr[12] = {5, 1, 1, 5, 1, 1, 5, 1, 1, 5, 1, 1};
    int a[5] = {5,1,0,2, 4};
    swap(a, 0, 4);
    print_array(a, 5);

    std::thread threads[4];
    bool results[4] = {false};
    int tc = 4;
    int len = 12;
    int step = (len - 1)/ tc;
    int prev = 0;
    for (int i = 0; i < tc; ++i) {
        int start = prev;
        int end = prev + step;
        threads[i] = std::thread(swap, arr, start, end);
        std::cout << "args: " << start << ", " << end << "\n";
        prev = end + 1;
    }
    for(std::thread& thread : threads){
        thread.join();
    }
    print_array(arr, 12);
    std::cout << mt_search(arr, len, tc, 5) << "\n";
    rand_arr(arr, len, 5);
    std::cout << "before\n";
    print_array(arr, 12);
    std::cout << "after\n";
    std::cout << mt_search(arr, len, tc, 6) << "\n";   
    print_array(arr, 12);
}

void rand_arr(int* arr, int len, int uniqueValue) {
    for(int i = 0; i < len; ++i){
        arr[i] = uniqueValue - (std::rand() % uniqueValue + 1);
    }
    arr[0] = uniqueValue;
}

void mswap(Work w){
    for(;w.start < w.end; ++w.start){
        if(w.arr[w.start] > w.arr[w.start + 1]){
            int temp = w.arr[w.start];
            w.arr[w.start] = w.arr[w.start + 1];
            w.arr[w.start + 1] = temp;
        }
    }
}

void thread_task(Work w){
    mswap(w);
    if(w.arr[w.end] == w.key){
        *w.is_found = true;
        return;
    }
    w.result = w.arr[w.end] > w.key ? in : not_in;
}

typedef struct SubWork{
    int* arr;
    int len;
    const int tc;
    int key;
    Work* w;
    bool* is_found;
} SubWork;

void sub_search(SubWork w){
    std::thread threads[w.tc];
    int step = (w.len - 1)/ w.tc;
    int prev = 0, start, end;
    for (int i = 0; i < w.tc; ++i) {
        start = prev;
        end = prev + step;
        //w.w[i] = {start, end, arr, w.key, 0,  w.is_found};
        //threads[i] = std::thread(thread_task, w[i];
        prev = end + 1;
    }
    for(std::thread& thread : threads){
        thread.join();
    }
}

bool multithreaded_search(int* arr, int len, const int tc, int key){
    std::thread threads[tc];
    Work w[tc];
    int step = (len - 1)/ tc;
    int prev = 0, start, end;
    bool is_found = false;
    for (int i = 0; i < tc; ++i) {
        start = prev;
        end = prev + step;
        w[i] = {start, end, arr, key, 0,  &is_found};
        //threads[i] = std::thread(thread_task, w[i];
        prev = end + 1;
    }
    for(std::thread& thread : threads){
        thread.join();
    }
    int tasks = 0;
    int task_p_thread[tc];
    if(is_found){
        return true;
    } else{
        while(!is_found){
            for (int i = 0; i < tc; ++i) {
                if (w[i].result == not_in){
                    continue;
                } else{
                    ++tasks;
                }
            }
            if(tasks == 0){
                return false;
            }
            int leftover = tc - tasks;
            int thing[tasks];
            for(int i = 0; i < tasks; ++i){
                thing[i] = 1;
            }
            for(int i = 0; i < leftover; ++i){
                thing[tasks] += 1;
            }
            Work nw[tc];
            int cur_thread = 0;
            for(int i = 0; i < tasks; ++i){
                SubWork work = {&w[i].arr[w[i].start], w[i].start - w[i].end, thing[i], key, &nw[cur_thread], &is_found};
                threads[i] = std::thread(sub_search, (work));
            }
            for(std::thread& thread : threads){
                thread.join();
            }
        }
    }
    return false;
}

typedef struct ThreadState{
    int* arr;
    int key;
    bool* FOUND;
    bool done;
    int start;
    int end;
    bool is_in;
} ThreadState;

void tswap(ThreadState s){
    for(;s.start < s.end; ++s.start){
        if(s.arr[s.start] > s.arr[s.start + 1]){
            int temp = s.arr[s.start];
            s.arr[s.start] = s.arr[s.start + 1];
            s.arr[s.start + 1] = temp;
        }
    }
    std::cout << "did\n";
}

void thread_work(ThreadState* state){
    while (RUNNING){
        if(state->done){
            continue;
        } else{
            tswap(*state);
            //swap(state->arr, state->start, state->end);
            if(state->arr[state->end] == state->key){
                *state->FOUND = true;
                return;
            }
            state->is_in = state->arr[state->end] > state->key ? in : not_in;
            state->done = true;
        }
    }
}

typedef struct ToDo{
    int start;
    int end;
} ToDo;

bool mt_search(int* arr, int len, const int tc, int key){
    std::thread threads[tc];
    ThreadState ts[tc];
    bool FOUND;
    RUNNING = true;
    int i, start, end, prev = 0;
    int step = (len - 1)/ tc;
    for (i = 0; i < tc; ++i) {
        start = prev;
        end = prev + step;
        ts[i] = {arr, key, &FOUND, false, start, end, in};
        threads[i] = std::thread{thread_work, &ts[i]};
        prev = end + 1;
    }
    std::vector<ToDo> work;
    int idle = 0;
    int times = 0;
    while(idle < tc && !FOUND){
        idle = 0;
        for(i = 0; i < tc; ++i){
            if(ts[i].done){
                if (ts[i].is_in){
                    ts[i].end = (ts[i].start + (ts[i].end - 1))/ 2;
                    ts[i].is_in = false;
                    if(ts[i].start - ts[i].end != 0){
                        ts[i].done = false;
                    } else{
                        ts[i].is_in = false;
                    }
                    if((ts[i].start + (ts[i].end - 1))/ 2-  ts[i].end != 0){
                    work.push_back({(ts[i].start + (ts[i].end - 1))/ 2, ts[i].end});

                    }
                } else{
                    if(!work.empty()){
                        ToDo todo = work.back();
                        ts[i].start = todo.start;
                        ts[i].end = todo.end;
                        ts[i].done = false;
                        work.pop_back();
                    } else{
                        ++idle;
                    }
                }
            }
            if(times < 10){
                print_array(arr, 12);
                ++times;
            }
        }
    }
    RUNNING = false;
    for(std::thread& thread : threads){
        thread.join();
    }
    return FOUND;
}

void swap(int* arr, int cur, int end){
    for(;cur < end; ++cur){
        if(arr[cur] > arr[cur + 1]){
            int temp = arr[cur];
            arr[cur] = arr[cur + 1];
            arr[cur + 1] = temp;
        }
    }
}
void print_array(int* arr, int len){
    for(int i = 0; i < len; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

bool binary_search(int* arr, int low, int high, int key){
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(arr[mid] == key){
            return true;
        }
        if(arr[mid] < key){
            low = mid + 1;
        } else{
            high = mid - 1;
        }
    }
    return false;
}
