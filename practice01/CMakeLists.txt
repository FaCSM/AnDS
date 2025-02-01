cmake_minimum_required(VERSION 3.26)
project(A_SD)

set(CMAKE_CXX_STANDARD 17)

add_executable(A_SD main.cpp
        rpn.h
        structures/dl_list.cpp
        structures/dynamic_array.cpp
        structures/stack.cpp
        application.cpp
        structures/dl_list.h
        structures/dynamic_array.h
        structures/stack.h
        application.h
)
