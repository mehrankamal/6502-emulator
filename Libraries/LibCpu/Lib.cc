#include "Lib.hh"
#include "Cpu.hh"
#include "Flag.hh"
#include "Instruction.hh"
#include <iostream>

namespace MOS6502 {
void Cpu::reset() {
  m_pc = 0x0400;
  m_sp = 0xFF;
  m_accumulator = 0;
  m_x = 0;
  m_y = 0;
  m_status = 0x20;
}

Instruction Cpu::fetch(Memory const &memory) {
  return static_cast<Instruction>(fetch_raw(memory));
}

Byte Cpu::fetch_location(Memory const &memory, Byte location) const {
  auto data = memory[location];
  return data;
}

Byte Cpu::fetch_raw(Memory const &memory) {
  auto data = memory[m_pc];
  m_pc++;
  return data;
}

Byte Cpu::fetch_current_address(Memory const &memory) {
  auto addr = fetch_raw(memory);
  auto data = fetch_location(memory, addr);
  return data;
}

Instruction Cpu::decode(Byte byte) {
  // TODO: Use a better strategy to decode byte into corresponding instruction
  // type
  return static_cast<Instruction>(byte);
}

void Cpu::execute_instruction(Instruction opcode, Memory &memory) {
  switch (opcode) {
  case Instruction::LDA: {
    m_accumulator = fetch_current_address(memory);
    update_zero_negative_flags(accumulator());
  } break;
  case Instruction::LDX: {
    m_x = fetch_current_address(memory);
    update_zero_negative_flags(x());
  } break;
  case Instruction::LDY: {
    m_y = fetch_current_address(memory);
    update_zero_negative_flags(y());
  }
  case Instruction::BRK:
    break;
  default:
    std::cout << "Unknown opcode: " << std::hex << (int)opcode << std::endl;
  }
}

void Cpu::update_zero_negative_flags(Byte reg) {
  if (reg == 0) {
    m_status |= to_underlying(Flag::Zero);
  }

  if (reg & 0b01000000) {
    m_status |= to_underlying(Flag::Negative);
  }
}

void Cpu::dump_registers() const {
  std::cout << "PC: " << std::hex << pc() << std::endl;
  std::cout << "SP: " << std::hex << sp() << std::endl;
  std::cout << "A: " << std::hex << (int)accumulator() << std::endl;
  std::cout << "X: " << std::hex << (int)x() << std::endl;
  std::cout << "Y: " << std::hex << (int)y() << std::endl;
  std::cout << "Status: " << std::endl;
  std::cout << "  Zero:     "
            << ((status() & to_underlying(Flag::Zero)) ? 1 : 0) << std::endl;
  std::cout << "  Negative: "
            << ((status() & to_underlying(Flag::Negative)) ? 1 : 0)
            << std::endl;
}

} // namespace MOS6502