cmake_minimum_required(VERSION 3.27)
project(PermutationGenerator)

set(CMAKE_CXX_STANDARD 17)

add_executable(PermutationGenerator
        src/Main.cpp
        include/Main.h
        src/sys_Utils.cpp
        include/sys_Utils.h
)

target_include_directories(PermutationGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
