#pragma once

#include "Types.hh"

namespace MOS6502 {
template <typename T> inline Byte to_underlying(T instruction) {
  return static_cast<Byte>(instruction);
}
} // namespace MOS6502
