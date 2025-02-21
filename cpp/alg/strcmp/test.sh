#!/bin/bash

echo "lin"
g++ -g -march=x86-64-v4 -mavx512f lin.cpp -o m
#g++ -msse4 lin.cpp -o m
perf stat -d ./m

echo "lib"
g++ -g -O2 -march=x86-64-v4 -mavx512f lib.cpp -o m
#g++ lib.cpp -o m
perf stat -d ./m

echo "128 simd"
#g++ -msse4.1 128.cpp -o m
g++ -g -O2 -march=x86-64-v4 -mavx512f 128.cpp -o m
perf stat -d ./m

echo "duck"
g++ -g -O2 -march=x86-64-v4 -mavx512f duck.cpp -o m
perf stat -d ./m 10000

echo "512 simd"
g++ -g -O2 -march=x86-64-v4 -mavx512f 512.cpp -o m
perf stat -d ./m 10000

echo "512 simd ptr"
g++ -g -O2 -march=x86-64-v4 -mavx512f 512ptr.cpp -o m
perf stat -d ./m 10000
