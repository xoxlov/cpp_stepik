cmake_minimum_required(VERSION 3.14)
project(MathSolutions)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp libs/gauss.cpp libs/gauss.h libs/matrix.tpp libs/matrix.h)

add_executable(MathSolutions ${SOURCE_FILES})
