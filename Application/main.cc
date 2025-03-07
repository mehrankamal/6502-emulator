#include <iostream>

using u8 = u_int8_t;
using u16 = unsigned short;

namespace MOS6502 {

using Byte = u8;
using Word = u16;

constexpr u16 KB = 1024;
class Memory {
public:
  Memory() { m_memory.resize(64 * KB); }
  ~Memory() {}

  Byte operator[](u16 address) const { return m_memory[address]; }
  Byte &operator[](u16 address) { return m_memory[address]; }

private:
  std::vector<Byte> m_memory;
};

enum class Instruction {
  LDA = 0xA9,
  BRK = 0x00,
};

enum class Flag {
  Zero = 0b00000010,
  Negative = 0b10000000,
};

Byte to_underlying(Flag instruction) { return static_cast<Byte>(instruction); }

class Cpu {
public:
  Cpu() {}
  ~Cpu() {}

  Word pc() const { return m_pc; }
  Byte sp() const { return m_sp; }

  Byte accumulator() const { return m_accumulator; }
  Byte x() const { return m_x; }
  Byte y() const { return m_y; }

  Byte status() const { return m_status; }

  void reset() {
    m_pc = 0x0400;
    m_sp = 0xFF;
    m_accumulator = 0;
    m_x = 0;
    m_y = 0;
    m_status = 0x20;
  }

  Instruction fetch(Memory const &memory) {
    return static_cast<Instruction>(fetch_raw(memory));
  }

  Byte fetch_raw(Memory const &memory) {
    auto data = memory[m_pc];
    m_pc++;
    return data;
  }

  void execute_instruction(Instruction opcode, Memory &memory) {
    switch (opcode) {
    case Instruction::LDA: // LDA Immediate
    {
      auto data = fetch_raw(memory);
      m_accumulator = data;
      update_zero_negative_flags(accumulator());
    } break;
    case Instruction::BRK:
      m_pc = 0x0402;
      break;
    default:
      std::cout << "Unknown opcode: " << std::hex << (int)opcode << std::endl;
      break;
    }
  }

  void dump_registers() const {
    std::cout << "PC: " << std::hex << pc() << std::endl;
    std::cout << "SP: " << std::hex << sp() << std::endl;
    std::cout << "A: " << std::hex << (int)accumulator() << std::endl;
    std::cout << "X: " << std::hex << x() << std::endl;
    std::cout << "Y: " << std::hex << y() << std::endl;
    std::cout << "Status: " << std::endl;
    std::cout << "  Zero: " << ((status() & to_underlying(Flag::Zero)) ? 1 : 0)
              << std::endl;
    std::cout << "  Negative: "
              << ((status() & to_underlying(Flag::Negative)) ? 1 : 0)
              << std::endl;
  }

  void update_zero_negative_flags(Byte reg) {
    if (reg == 0) {
      m_status |= to_underlying(Flag::Zero);
    }

    if (reg & 0b01000000) {
      m_status |= to_underlying(Flag::Negative);
    }
  }

private:
  Word m_pc;
  Byte m_sp;

  Byte m_accumulator;
  Byte m_x;
  Byte m_y;

  Byte m_status;
};

} // namespace MOS6502

int main(int argc, char *argv[]) {
  MOS6502::Memory memory;
  MOS6502::Cpu cpu;

  // LDA 100
  memory[0x0400] = 0xA9; // LDA
  memory[0x0401] = 0x01; // 100
  memory[0x0402] = 0x00; // BRK

  cpu.reset();
  while (true) {
    auto opcode = cpu.fetch(memory);
    cpu.execute_instruction(opcode, memory);

    if (cpu.pc() == 0x0402) {
      break;
    }
  }

  std::cout << "Program finished" << std::endl;

  cpu.dump_registers();

  return 0;
}