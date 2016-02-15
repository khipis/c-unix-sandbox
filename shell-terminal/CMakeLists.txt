cmake_minimum_required(VERSION 3.3)
project(shell_terminal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    shell
    shell.c)

add_executable(shell_terminal ${SOURCE_FILES})