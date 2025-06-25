#pragma once

#include <map>
#include "bimap.h"
// Instruction and their valid addressing modes
static const map<Instruction, vector<AddressMode>> instruction_to_token_types =
{
    // Load/Store Operations
    {Instruction::LDA, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::LDX, {IMMEDIATE, ZERO_PAGE, Y_ZERO_PAGE, ABSOLUTE, Y_ABSOLUTE}},
    {Instruction::LDY, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},
    {Instruction::STA, {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::STX, {ZERO_PAGE, Y_ZERO_PAGE, ABSOLUTE}},
    {Instruction::STY, {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE}},

    // Register Transfers
    {Instruction::TAX, {IMPLIED}},
    {Instruction::TAY, {IMPLIED}},
    {Instruction::TXA, {IMPLIED}},
    {Instruction::TYA, {IMPLIED}},

    // Stack Operations
    {Instruction::TSX, {IMPLIED}},
    {Instruction::TXS, {IMPLIED}},
    {Instruction::PHA, {IMPLIED}},
    {Instruction::PHP, {IMPLIED}},
    {Instruction::PLA, {IMPLIED}},
    {Instruction::PLP, {IMPLIED}},

    // Logical
    {Instruction::AND, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::EOR, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::ORA, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::BIT, {ZERO_PAGE, ABSOLUTE}},

    // Arithmetic
    {Instruction::ADC, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::SBC, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::CMP, {IMMEDIATE, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {Instruction::CPX, {IMMEDIATE, ZERO_PAGE, ABSOLUTE}},
    {Instruction::CPY, {IMMEDIATE, ZERO_PAGE, ABSOLUTE}},

    // Increments & Decrements
    {Instruction::INC, {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},
    {Instruction::INX, {IMPLIED}},
    {Instruction::INY, {IMPLIED}},
    {Instruction::DEC, {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},
    {Instruction::DEX, {IMPLIED}},
    {Instruction::DEY, {IMPLIED}},

    // Shifts
    {Instruction::ASL, {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},
    {Instruction::LSR, {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},
    {Instruction::ROL, {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},
    {Instruction::ROR, {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE, X_ABSOLUTE}},

    // Jumps & Calls
    {Instruction::JMP, {ABSOLUTE, ABS_INDIRECT}},
    {Instruction::JSR, {ABSOLUTE}},
    {Instruction::RTS, {IMPLIED}},

    // Branches
    {Instruction::BCC, {RELATIVE}},
    {Instruction::BCS, {RELATIVE}},
    {Instruction::BEQ, {RELATIVE}},
    {Instruction::BMI, {RELATIVE}},
    {Instruction::BNE, {RELATIVE}},
    {Instruction::BPL, {RELATIVE}},
    {Instruction::BVC, {RELATIVE}},
    {Instruction::BVS, {RELATIVE}},

    // Status Flag Changes
    {Instruction::CLC, {IMPLIED}},
    {Instruction::CLD, {IMPLIED}},
    {Instruction::CLI, {IMPLIED}},
    {Instruction::CLV, {IMPLIED}},
    {Instruction::SEC, {IMPLIED}},
    {Instruction::SED, {IMPLIED}},
    {Instruction::SEI, {IMPLIED}},

    // System Functions
    {Instruction::BRK, {IMPLIED}},
    {Instruction::NOP, {IMPLIED}},
    {Instruction::RTI, {IMPLIED}},
};

inline const auto& instruction_opcode_bimap = construct_bimap();