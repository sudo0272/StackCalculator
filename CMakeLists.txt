project(StackCalculator)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE lib lib/*.cpp lib/*.h)
file(GLOB_RECURSE src src/*.cpp)

add_executable(StackCalculator ${lib} ${src})
