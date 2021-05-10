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
    std::cout << '\n';
    std::sort(buf.begin(), buf.end());
    for (auto& i : buf) {
        std::cout << i << ' ';
    }
    return 0;
}