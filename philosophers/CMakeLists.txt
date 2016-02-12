cmake_minimum_required(VERSION 3.3)
project(philosophers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        philosophers_deadlock.c
  )

add_executable(philosophers ${SOURCE_FILES})

target_link_libraries(philosophers pthread)