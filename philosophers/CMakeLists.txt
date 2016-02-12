cmake_minimum_required(VERSION 3.3)
project(philosophers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DEADLOCK
        philosophers_deadlock.c
        )

set(STARVATION
        philosophers_starvation.c
        )


add_executable(deadlock ${DEADLOCK})

add_executable(starvation ${STARVATION})

target_link_libraries(deadlock pthread)
target_link_libraries(starvation pthread)