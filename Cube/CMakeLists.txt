cmake_minimum_required(VERSION 3.19)
project(Cube)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cube main.cpp cube.cpp GeneticAlgorithm.cpp)