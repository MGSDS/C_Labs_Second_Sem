#include <iostream>
#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> buf;
    buf.push_back(3);
    buf.push_back(1);
    buf.push_back(5);
    std::sort(buf.begin(), buf.end());
    std::cout<<(buf.at(4));
    return 0;
}