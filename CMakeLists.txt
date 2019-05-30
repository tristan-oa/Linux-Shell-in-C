cmake_minimum_required(VERSION 3.13)
project(OS_ASSIGNMENT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")


add_executable(OS_ASSIGNMENT eggshell.c linenoise.c)
