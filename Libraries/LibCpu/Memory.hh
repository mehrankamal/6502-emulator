#pragma once

#include "Types.hh"
#include <vector>

namespace MOS6502 {
class Memory {
public:
  Memory() { m_memory.resize(64 * KB); }
  ~Memory() {}

  Byte operator[](u16 address) const { return m_memory[address]; }
  Byte &operator[](u16 address) { return m_memory[address]; }

private:
  std::vector<Byte> m_memory;
};
} // namespace MOS6502