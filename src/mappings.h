#pragma once
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "instructions.h"

using Op = Operation;
using i = Instruction;
using a = AddressMode;

static const std::map<Instruction, std::vector<AddressMode>> instruction_to_valid_address_modes =
{
    // Load/Store Operations
    {i::LDA, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::LDX, {a::IMMEDIATE, a::ZERO_PAGE, a::Y_ZERO_PAGE, a::ABSOLUTE, a::Y_ABSOLUTE}},
    {i::LDY, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},
    {i::STA, {a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::STX, {a::ZERO_PAGE, a::Y_ZERO_PAGE, a::ABSOLUTE}},
    {i::STY, {a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE}},

    // Register Transfers
    {i::TAX, {a::IMPLIED}},
    {i::TAY, {a::IMPLIED}},
    {i::TXA, {a::IMPLIED}},
    {i::TYA, {a::IMPLIED}},

    // Stack Operations
    {i::TSX, {a::IMPLIED}},
    {i::TXS, {a::IMPLIED}},
    {i::PHA, {a::IMPLIED}},
    {i::PHP, {a::IMPLIED}},
    {i::PLA, {a::IMPLIED}},
    {i::PLP, {a::IMPLIED}},

    // Logical
    {i::AND, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::EOR, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::ORA, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::BIT, {a::ZERO_PAGE, a::ABSOLUTE}},

    // Arithmetic
    {i::ADC, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::SBC, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::CMP, {a::IMMEDIATE, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE, a::Y_ABSOLUTE, a::X_INDEX_ZP_INDIRECT, a::ZP_INDIRECT_Y_INDEX}},
    {i::CPX, {a::IMMEDIATE, a::ZERO_PAGE, a::ABSOLUTE}},
    {i::CPY, {a::IMMEDIATE, a::ZERO_PAGE, a::ABSOLUTE}},

    // Increments & Decrements
    {i::INC, {a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},
    {i::INX, {a::IMPLIED}},
    {i::INY, {a::IMPLIED}},
    {i::DEC, {a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},
    {i::DEX, {a::IMPLIED}},
    {i::DEY, {a::IMPLIED}},

    // Shifts
    {i::ASL, {a::ACCUMULATOR, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},
    {i::LSR, {a::ACCUMULATOR, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},
    {i::ROL, {a::ACCUMULATOR, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},
    {i::ROR, {a::ACCUMULATOR, a::ZERO_PAGE, a::X_ZERO_PAGE, a::ABSOLUTE, a::X_ABSOLUTE}},

    // Jumps & Calls
    {i::JMP, {a::ABSOLUTE, a::ABS_INDIRECT}},
    {i::JSR, {a::ABSOLUTE}},
    {i::RTS, {a::IMPLIED}},

    // Branches
    {i::BCC, {a::RELATIVE}},
    {i::BCS, {a::RELATIVE}},
    {i::BEQ, {a::RELATIVE}},
    {i::BMI, {a::RELATIVE}},
    {i::BNE, {a::RELATIVE}},
    {i::BPL, {a::RELATIVE}},
    {i::BVC, {a::RELATIVE}},
    {i::BVS, {a::RELATIVE}},

    // Status Flag Changes
    {i::CLC, {a::IMPLIED}},
    {i::CLD, {a::IMPLIED}},
    {i::CLI, {a::IMPLIED}},
    {i::CLV, {a::IMPLIED}},
    {i::SEC, {a::IMPLIED}},
    {i::SED, {a::IMPLIED}},
    {i::SEI, {a::IMPLIED}},

    // System Functions
    {i::BRK, {a::IMPLIED}},
    {i::NOP, {a::IMPLIED}},
    {i::RTI, {a::IMPLIED}},

    // Custom Functions
    {i::PRT, {a::IMPLIED}}
};

static const std::vector<Operation> opcode_to_operation_lookup = {
    {Op{ i::BRK, a::IMPLIED }},   {Op{ i::ORA, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::ORA, a::ZERO_PAGE }},   {Op{ i::ASL, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::PHP, a::IMPLIED }}, {Op{ i::ORA, a::IMMEDIATE }},   {Op{ i::ASL, a::ACCUMULATOR }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::ORA, a::ABSOLUTE }},   {Op{ i::ASL, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BPL, a::RELATIVE }},  {Op{ i::ORA, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::ORA, a::X_ZERO_PAGE }}, {Op{ i::ASL, a::X_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CLC, a::IMPLIED }}, {Op{ i::ORA, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::ORA, a::X_ABSOLUTE }}, {Op{ i::ASL, a::X_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::JSR, a::ABSOLUTE }},  {Op{ i::AND, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::BIT, a::ZERO_PAGE }},   {Op{ i::ADC, a::ZERO_PAGE }},   {Op{ i::ROL, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::PLP, a::IMPLIED }}, {Op{ i::AND, a::IMMEDIATE }},   {Op{ i::ROL, a::ACCUMULATOR }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::BIT, a::ABSOLUTE }},     {Op{ i::AND, a::ABSOLUTE }},   {Op{ i::ROL, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BMI, a::RELATIVE }},  {Op{ i::AND, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::ADC, a::X_ZERO_PAGE }}, {Op{ i::ROL, a::X_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::SEC, a::IMPLIED }}, {Op{ i::AND, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::AND, a::X_ABSOLUTE }}, {Op{ i::ROL, a::X_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::RTI, a::IMPLIED }},   {Op{ i::EOR, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::EOR, a::ZERO_PAGE }},   {Op{ i::LSR, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::PHA, a::IMPLIED }}, {Op{ i::EOR, a::IMMEDIATE }},   {Op{ i::LSR, a::ACCUMULATOR }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::JMP, a::ABSOLUTE }},     {Op{ i::EOR, a::ABSOLUTE }},   {Op{ i::LSR, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BVC, a::RELATIVE }},  {Op{ i::EOR, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::EOR, a::X_ZERO_PAGE }}, {Op{ i::LSR, a::X_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CLI, a::IMPLIED }}, {Op{ i::EOR, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::EOR, a::X_ABSOLUTE }}, {Op{ i::LSR, a::X_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::RTS, a::IMPLIED }},   {Op{ i::ADC, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::ADC, a::ZERO_PAGE }},   {Op{ i::ROR, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::PLA, a::IMPLIED }}, {Op{ i::ADC, a::IMMEDIATE }},   {Op{ i::ROR, a::ACCUMULATOR }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::JMP, a::ABS_INDIRECT }}, {Op{ i::ADC, a::ABSOLUTE }},   {Op{ i::ROR, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BVS, a::RELATIVE }},  {Op{ i::ADC, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::ADC, a::X_ZERO_PAGE }}, {Op{ i::ROR, a::X_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::SEI, a::IMPLIED }}, {Op{ i::ADC, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::ADC, a::X_ABSOLUTE }}, {Op{ i::ROR, a::X_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::PRT, a::IMPLIED}},    {Op{ i::STA, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::STY, a::ZERO_PAGE }},   {Op{ i::STA, a::ZERO_PAGE }},   {Op{ i::STX, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::DEY, a::IMPLIED }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::TXA, a::IMPLIED }},     {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::STY, a::ABSOLUTE }},     {Op{ i::STA, a::ABSOLUTE }},   {Op{ i::STX, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BCC, a::RELATIVE }},  {Op{ i::STA, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::STY, a::X_ZERO_PAGE }}, {Op{ i::STA, a::X_ZERO_PAGE }}, {Op{ i::STX, a::Y_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::TYA, a::IMPLIED }}, {Op{ i::STA, a::Y_ABSOLUTE }},  {Op{ i::TXS, a::IMPLIED }},     {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::STA, a::X_ABSOLUTE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::LDY, a::IMMEDIATE }}, {Op{ i::LDA, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::LDX, a::IMMEDIATE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::LDY, a::ZERO_PAGE }},   {Op{ i::LDA, a::ZERO_PAGE }},   {Op{ i::LDX, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::TAY, a::IMPLIED }}, {Op{ i::LDA, a::IMMEDIATE }},   {Op{ i::TAX, a::IMPLIED }},     {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::LDY, a::ABSOLUTE }},     {Op{ i::LDA, a::ABSOLUTE }},   {Op{ i::LDX, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BCS, a::RELATIVE }},  {Op{ i::LDA, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::LDY, a::X_ZERO_PAGE }}, {Op{ i::LDA, a::X_ZERO_PAGE }}, {Op{ i::LDX, a::Y_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CLV, a::IMPLIED }}, {Op{ i::LDA, a::Y_ABSOLUTE }},  {Op{ i::TSX, a::IMPLIED }},     {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::LDY, a::X_ABSOLUTE }},   {Op{ i::LDA, a::X_ABSOLUTE }}, {Op{ i::LDX, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::CPY, a::IMMEDIATE }}, {Op{ i::CMP, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CPY, a::ZERO_PAGE }},   {Op{ i::CMP, a::ZERO_PAGE }},   {Op{ i::DEC, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INY, a::IMPLIED }}, {Op{ i::CMP, a::IMMEDIATE }},   {Op{ i::DEX, a::IMPLIED }},     {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CPY, a::ABSOLUTE }},     {Op{ i::CMP, a::ABSOLUTE }},   {Op{ i::DEC, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BNE, a::RELATIVE }},  {Op{ i::CMP, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CMP, a::X_ZERO_PAGE }}, {Op{ i::DEC, a::X_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CLD, a::IMPLIED }}, {Op{ i::CMP, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::CMP, a::X_ABSOLUTE }}, {Op{ i::DEC, a::X_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::CPX, a::IMMEDIATE }}, {Op{ i::SBC, a::X_INDEX_ZP_INDIRECT }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CPX, a::ZERO_PAGE }},   {Op{ i::SBC, a::ZERO_PAGE }},   {Op{ i::INC, a::ZERO_PAGE }},   {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INX, a::IMPLIED }}, {Op{ i::SBC, a::IMMEDIATE }},   {Op{ i::NOP, a::IMPLIED }},     {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::CPX, a::ABSOLUTE }},     {Op{ i::SBC, a::ABSOLUTE }},   {Op{ i::INC, a::ABSOLUTE }},    {Op{ i::INVALID, a::UNKNOWN }},
    {Op{ i::BEQ, a::RELATIVE }},  {Op{ i::SBC, a::ZP_INDIRECT_Y_INDEX }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::SBC, a::X_ZERO_PAGE }}, {Op{ i::INC, a::X_ZERO_PAGE }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::SED, a::IMPLIED }}, {Op{ i::SBC, a::Y_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }}, {Op{ i::INVALID, a::UNKNOWN }},  {Op{ i::SBC, a::X_ABSOLUTE }}, {Op{ i::INC, a::X_ABSOLUTE }},  {Op{ i::INVALID, a::UNKNOWN }},
};

static const std::unordered_map<std::string, Instruction> string_to_instruction = {
    { "LDA", i::LDA }, { "LDX", i::LDX }, { "LDY", i::LDY }, { "STA", i::STA },
    { "STX", i::STX }, { "STY", i::STY }, { "TAX", i::TAX }, { "TAY", i::TAY },
    { "TXA", i::TXA }, { "TYA", i::TYA }, { "TSX", i::TSX }, { "TXS", i::TXS },
    { "PHA", i::PHA }, { "PHP", i::PHP }, { "PLA", i::PLA }, { "PLP", i::PLP },
    { "AND", i::AND }, { "EOR", i::EOR }, { "ORA", i::ORA }, { "BIT", i::BIT },
    { "ADC", i::ADC }, { "SBC", i::SBC }, { "CMP", i::CMP }, { "CPX", i::CPX },
    { "CPY", i::CPY }, { "INC", i::INC }, { "INX", i::INX }, { "INY", i::INY },
    { "DEC", i::DEC }, { "DEX", i::DEX }, { "DEY", i::DEY }, { "ASL", i::ASL },
    { "LSR", i::LSR }, { "ROL", i::ROL }, { "ROR", i::ROR }, { "JMP", i::JMP },
    { "JSR", i::JSR }, { "RTS", i::RTS }, { "BCC", i::BCC }, { "BCS", i::BCS },
    { "BEQ", i::BEQ }, { "BMI", i::BMI }, { "BNE", i::BNE }, { "BPL", i::BPL },
    { "BVC", i::BVC }, { "BVS", i::BVS }, { "CLC", i::CLC }, { "CLD", i::CLD },
    { "CLI", i::CLI }, { "CLV", i::CLV }, { "SEC", i::SEC }, { "SED", i::SED },
    { "SEI", i::SEI }, { "BRK" ,i::BRK }, { "NOP", i::NOP }, { "RTI", i::RTI },
    { "PRT", i::PRT }
};

inline Instruction get_instruction(const std::string& str) {
    auto it = string_to_instruction.find(str);
    if (it != string_to_instruction.end()) {
        return it->second;
    }
    return Instruction::INVALID;
}

static const std::unordered_set<std::string> valid_instructions =
{ "LDA", "LDX", "LDY", "STA", "STX", "STY", "TAX", "TAY", "TXA", "TYA", "TSX", "TXS", "PHA", "PHP",
  "PLA", "PLP", "AND", "EOR", "ORA", "BIT", "ADC", "SBC", "CMP", "CPX", "CPY", "INC", "INX", "INY",
  "DEC", "DEX", "DEY", "ASL", "LSR", "ROL", "ROR", "JMP", "JSR", "RTS", "BCC", "BCS", "BEQ", "BMI",
  "BNE", "BPL", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "SEC", "SED", "SEI", "BRK", "NOP", "RTI",
  "PRT" };