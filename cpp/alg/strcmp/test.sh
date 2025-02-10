#!/bin/bash

echo "lin"
g++ -msse4 lin.cpp -o m
perf stat -d ./m

echo "lib"
g++ lib.cpp -o m
perf stat -d ./m

echo "128 simd"
g++ -msse4.1 main.cpp -o m
perf stat -d ./m
