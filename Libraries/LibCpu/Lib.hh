#pragma once

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
  LDX = 0xA2,
  LDY = 0xA0,
  BRK = 0x00,
};

enum class Flag {
  Zero = 0b00000010,
  Negative = 0b10000000,
};

template <typename T> inline Byte to_underlying(T instruction) {
  return static_cast<Byte>(instruction);
}

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

  void reset();
  Instruction fetch(Memory const &);
  Byte fetch_raw(Memory const &);
  Byte fetch_current_address(Memory const &);
  Instruction decode(Byte);
  Byte fetch_location(Memory const &, Byte) const;
  void execute_instruction(Instruction, Memory &);
  void update_zero_negative_flags(Byte);
  void dump_registers() const;

private:
  Word m_pc;
  Byte m_sp;

  Byte m_accumulator;
  Byte m_x;
  Byte m_y;

  Byte m_status;
};

} // namespace MOS6502
