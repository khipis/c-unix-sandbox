cmake_minimum_required(VERSION 3.3)
project(a51_generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        lfsr.c)

add_executable(a51_generator ${SOURCE_FILES})