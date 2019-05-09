cmake_minimum_required(VERSION 3.12)
project(NFA)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(NFA
        include/Estado.h
        include/NFA.h
        src/Estado.cpp
        src/main.cpp
        src/NFA.cpp)
