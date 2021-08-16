cmake_minimum_required(VERSION 3.16)

PROJECT(hgardenpi-protocol VERSION "0.10.0" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(hgardenpi-protocol main.cpp)
