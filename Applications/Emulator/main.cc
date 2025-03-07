#include <iostream>

#include "Lib.hh"

int main() {
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