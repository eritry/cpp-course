cmake_minimum_required(VERSION 3.10.2)
project(lib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES huffman.cpp tree.cpp huffman_testing.cpp)

set(HEADERS huffman.h tree.h)

add_library(lib STATIC ${SOURCES} ${HEADERS})

add_executable(testing huffman_testing.cpp gtest/gtest-all.cc gtest/gtest.h gtest/gtest_main.cc)

target_link_libraries(testing lib -lpthread)