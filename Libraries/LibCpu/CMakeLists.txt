
add_library(LibCpu STATIC Lib.cc)
target_include_directories(LibCpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})