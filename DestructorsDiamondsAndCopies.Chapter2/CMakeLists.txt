cmake_minimum_required(VERSION 3.5)

project(chapter2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chapter2 main.cpp)
add_executable(virtual_destroy virtual_destroy.cpp)
add_executable(virtual_forbidden virtual_forbidden.cpp)
