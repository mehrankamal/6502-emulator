cmake_minimum_required(VERSION 3.31)

project(6502Emulator VERSION 0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Libraries)
add_subdirectory(Applications)
