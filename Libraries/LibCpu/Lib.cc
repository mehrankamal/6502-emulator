#include "Lib.hh"

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

Byte Cpu::fetch_raw(Memory const &memory) {
  auto data = memory[m_pc];
  m_pc++;
  return data;
}

void Cpu::execute_instruction(Instruction opcode, Memory &memory) {
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

void Cpu::update_zero_negative_flags(Byte reg) {
  if (reg == 0) {
    m_status |= to_underlying(Flag::Zero);
  }

  if (reg & 0b01000000) {
    m_status |= to_underlying(Flag::Negative);
  }
}

} // namespace MOS6502