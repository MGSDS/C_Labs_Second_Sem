cmake_minimum_required(VERSION 3.17)
project(FifthLab)

set(CMAKE_CXX_STANDARD 20)

add_executable(FifthLab main.cpp CircularBuffer.cpp CircularBuffer.h iterator.cpp iterator.h)