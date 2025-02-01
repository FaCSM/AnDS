cmake_minimum_required(VERSION 3.26)
project(practice02)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        practice02 main.cpp
        application.cpp
        application.h
        ../practice01/structures/dl_list.h
        ../practice01/structures/dl_list.cpp
        stack/stack.cpp
        stack/stack.h
)
