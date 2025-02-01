cmake_minimum_required(VERSION 3.26)
project(practice03)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        practice03
        main.cpp
        application.cpp
        application.h
        trees/bin-tree.cpp
        trees/bin-tree.h
        trees/avl-tree.cpp
        trees/avl-tree.h

        stack.cpp
        stack.h
)
