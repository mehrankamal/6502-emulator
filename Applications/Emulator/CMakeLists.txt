add_executable(6502Emulator main.cc)

target_link_libraries(6502Emulator
    PRIVATE
    LibCpu
)

target_compile_options(6502Emulator
    PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
)
