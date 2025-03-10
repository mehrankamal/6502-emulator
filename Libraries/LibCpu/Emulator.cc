#include "Emulator.hh"
#include "Types.hh"
#include <cassert>
#include <fstream>
#include <ios>
#include <iostream>

namespace MOS6502 {
void Emulator::load_binary(std::string const& binary_path)
{
    std::ifstream file_buffer(binary_path, std::ios::binary | std::ios::in);
    file_buffer.seekg(std::ios::beg, std::ios::end);
    u32 file_size = file_buffer.tellg();

    file_buffer.seekg(std::ios::beg);

    assert(file_size <= 64 * KB);
    file_buffer.read((char*)m_memory.underlying().data(), file_size);
}

void Emulator::run()
{
    m_cpu.reset();

    m_memory.dump();

    while (true) {
        auto opcode_byte = m_cpu.fetch_raw(m_memory);
        std::cout << std::hex << (int)opcode_byte << std::endl;
        auto opcode = m_cpu.decode(opcode_byte);
        if (opcode == MOS6502::Instruction::BRK) {
            break;
        }
        m_cpu.execute_instruction(opcode, m_memory);

        std::cout << "----------------------------" << std::endl;
        m_cpu.dump_registers();
    }

    std::cout << "Program finished" << std::endl;

    m_cpu.dump_registers();
}
} // namespace MOS6502
