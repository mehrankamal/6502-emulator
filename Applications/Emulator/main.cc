#include <iostream>

#include "Lib.hh"
#include "LibCpu.hh"

int main() {
  MOS6502::Memory memory;
  MOS6502::Cpu cpu;

  // LDA 100
  memory[0x0000] = 0x95;
  memory[0x0001] = 0x21;
  memory[0x0400] = MOS6502::to_underlying(MOS6502::Instruction::LDA);
  memory[0x0401] = 0x00;
  memory[0x0402] = MOS6502::to_underlying(MOS6502::Instruction::LDX);
  memory[0x0403] = 0x01;
  memory[0x0404] = MOS6502::to_underlying(MOS6502::Instruction::BRK);

  cpu.reset();
  while (true) {
    auto opcode = cpu.fetch(memory);
    if(opcode == MOS6502::Instruction::BRK) {
      break;
    }
    cpu.execute_instruction(opcode, memory);

    std::cout << "----------------------------" << std::endl;
    cpu.dump_registers();
  }

  std::cout << "Program finished" << std::endl;

  cpu.dump_registers();

  return 0;
}