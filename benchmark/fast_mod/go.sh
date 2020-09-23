#!/bin/bash

echo "========================================================= -O2 ========================================================="
echo "========================================================="
echo "g++: static inline"
g++ -std=c++14 -march=native -O2 -g0 static_inline_bm.cc -o gsi
./gsi

echo "========================================================="
echo "g++: original"
g++ -std=c++14 -march=native -O2 -g0 original.cc -o gorig
./gorig


echo "========================================================="
echo "clang++: static inline"
clang++ -std=c++14 -march=native -O2 -g0 static_inline_bm.cc -o clsi
./clsi

echo "========================================================="
echo "clang++: original"
clang++ -std=c++14 -march=native -O2 -g0 original.cc -o clorig
./clorig

echo "========================================================= -O3 ========================================================="
echo "========================================================="
echo "g++: static inline"
g++ -std=c++14 -march=native -O3 -g0 static_inline_bm.cc -o gsi
./gsi

echo "========================================================="
echo "g++: original"
g++ -std=c++14 -march=native -O3 -g0 original.cc -o gorig
./gorig


echo "========================================================="
echo "clang++: static inline"
clang++ -std=c++14 -march=native -O3 -g0 static_inline_bm.cc -o clsi
./clsi

echo "========================================================="
echo "clang++: original"
clang++ -std=c++14 -march=native -O3 -g0 original.cc -o clorig
./clorig
