cmake_minimum_required(VERSION 3.26)
project(coursework)

set(CMAKE_CXX_STANDARD 20)

add_executable(coursework
        main.cpp
        application.h
        application.cpp
        structures/graph.cpp
        structures/graph.h
        structures/dsu.cpp
        structures/dsu.h
)
