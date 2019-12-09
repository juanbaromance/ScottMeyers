cmake_minimum_required(VERSION 3.5)

project(Chapter5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main.x  MyPerson.cpp MyPersonImpl.cpp main.cpp)
