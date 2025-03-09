#include <iostream>

#include <LibCpu.hh>

int main() {
  MOS6502::Memory memory;
  MOS6502::Cpu cpu;

  cpu.reset();
  while (true) {
    auto opcode_byte = cpu.fetch_raw(memory);
    auto opcode = cpu.decode(opcode_byte);
    if (opcode == MOS6502::Instruction::BRK) {
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