cmake_minimum_required(VERSION 3.16)

project(hello_world LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw-01-tic-tac-toe src/main.cpp)
