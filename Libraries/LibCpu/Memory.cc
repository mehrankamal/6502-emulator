#include "Memory.hh"
#include <ios>
#include <iostream>

namespace MOS6502 {
void Memory::dump() const {
  for (int i = 0; i < m_memory.size(); i++) {
    std::cout << std::hex << (int)m_memory[i] << " ";
    i++;
    while (i < m_memory.size() && i % KB) {
      std::cout << std::hex << (int)m_memory[i] << " ";
      i++;
    }
    std::cout << std::endl;
  }
}
} // namespace MOS6502