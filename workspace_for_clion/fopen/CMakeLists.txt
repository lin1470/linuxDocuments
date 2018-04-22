cmake_minimum_required(VERSION 3.7)
project(fopen)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hh/hello.cpp hello/hello.cpp)
add_executable(fopen ${SOURCE_FILES})