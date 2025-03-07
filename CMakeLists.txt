cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(6502Emulator CXX)

add_executable(6502Emulator
    Application/main.cc)
