add_library(LibCpu STATIC 
    Cpu.cc
    Emulator.cc
    Memory.cc
)
target_include_directories(LibCpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
