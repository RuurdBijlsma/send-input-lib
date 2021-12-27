cmake_minimum_required(VERSION 3.21)
project(click)

set(CMAKE_CXX_STANDARD 23)

add_library(click SHARED library.cpp)
