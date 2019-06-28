cmake_minimum_required(VERSION 2.8)
project(exam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined,leak -D_GLIBCXX_DEBUG")

add_executable(exam vector.h counted.h
        counted.cpp
        fault_injection.h
        fault_injection.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc
        vector_testing.cpp)
target_link_libraries(exam -lpthread)