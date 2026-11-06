#!/bin/bash
# Stress test: ./stress.sh  (needs sol.cpp, brute.cpp, gen.cpp; gen takes seed as argv[1])
g++ -O2 -std=c++17 sol.cpp -o sol; g++ -O2 -std=c++17 brute.cpp -o brute; g++ -O2 -std=c++17 gen.cpp -o gen
for ((i = 1; ; i++)); do
	./gen $i > in.txt
	./sol < in.txt > out1.txt; ./brute < in.txt > out2.txt
	if ! diff -q out1.txt out2.txt > /dev/null; then echo "DIFF on seed $i"; break; fi
done
