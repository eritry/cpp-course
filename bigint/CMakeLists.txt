    cmake_minimum_required(VERSION 2.8)

project(BIGINT)

include_directories(${BIGINT_SOURCE_DIR})

add_executable(
        big_integer_testing
        big_integer_testing.cpp
        big_integer.h
        big_integer.cpp
        bigint_vector.cpp
        bigint_vector.h

        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
target_link_libraries(big_integer_testing -lpthread)