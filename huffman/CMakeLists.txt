cmake_minimum_required(VERSION 3.10.2)
project(huffman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")
set(SOURCE_EXE main.cpp)

add_executable(huffman ${SOURCE_EXE})
add_subdirectory(lib)

target_link_libraries(huffman lib)