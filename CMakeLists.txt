cmake_minimum_required(VERSION 3.25)
project(Maturski)

set(CMAKE_CXX_STANDARD 20)

add_executable(Maturski main.cpp)
add_subdirectory(tests)
