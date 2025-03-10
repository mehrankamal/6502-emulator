#include <iostream>

#include <LibCpu.hh>

int main(int argc, char* argv[])
{
    MOS6502::Memory memory;
    MOS6502::Cpu cpu;
    MOS6502::Emulator emulator(cpu, memory);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <executable-path>" << std::endl;
    }
    emulator.load_binary(argv[1]);
    emulator.run();

    return 0;
}
