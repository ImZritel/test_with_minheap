BUILD:
g++ -o main.exe main.cpp -std=c++17 -O2

COMMENT ON LOGIC:
The solution uses "Min Heap" data structure.
We can't use order statistics algorithm (O(N)) by virtue of the assumption that available memory can't contain all input data.
