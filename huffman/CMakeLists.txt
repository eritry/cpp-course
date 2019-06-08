cmake_minimum_required(VERSION 3.10.2)
project(huffman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined,leak -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  ${CMAKE_CXX_FLAGS_RELEASE})

set(SOURCE_EXE main.cpp)

add_executable(huffman ${SOURCE_EXE})
add_subdirectory(lib)

target_link_libraries(huffman lib)
