cmake_minimum_required(VERSION 3.3)
project(http_echo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        http-echo.c)

add_executable(http_echo ${SOURCE_FILES})