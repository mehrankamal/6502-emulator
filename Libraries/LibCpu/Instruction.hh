#pragma once

namespace MOS6502 {
enum class Instruction {
    LDA = 0xA9,
    LDX = 0xA2,
    LDY = 0xA0,
    BRK = 0x00,
};
}
