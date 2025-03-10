#pragma once

#include "Cpu.hh"
#include "Memory.hh"
#include <string>

namespace MOS6502 {
class Emulator {
public:
    Emulator(Cpu cpu, Memory memory)
        : m_cpu(cpu)
        , m_memory(memory)
    {
    }

    void load_binary(std::string const& binary_path);
    void run();

private:
    Cpu m_cpu;
    Memory m_memory;
};
} // namespace MOS6502
