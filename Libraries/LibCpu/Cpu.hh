#include "Types.hh"

#include "Instruction.hh"
#include "Memory.hh"

namespace MOS6502 {
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