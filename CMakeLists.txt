cmake_minimum_required(VERSION 3.0)

project(R-BTree)

set(CMAKE_CXX_FLAGS "-std=c++11")
add_definitions("-Wall -g")
add_definitions(-Wno-builtin-macro-redefined)


add_executable(main main.cpp)


set(EXECUTABLE_OUTPUT_PATH ../bin)

set(LIBRARY_OUTPUT_PATH ../lib)