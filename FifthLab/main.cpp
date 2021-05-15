#include <iostream>
#include <algorithm>
#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> buf;
    buf.resize(5, 10);
    buf.pop_front();
    buf.pop_front();
    buf.pop_front();
    buf.push_back(7);
    buf.push_back(3);
    buf.push_back(100);
    for(int i = 0; i < 10; ++i){
        buf.push_back(rand());
    }
    std::cout << std::is_heap(buf.begin(), buf.end());
    std::make_heap(buf.begin(), buf.end());
    std::cout << std::is_heap(buf.begin(), buf.end());
    return 0;
}