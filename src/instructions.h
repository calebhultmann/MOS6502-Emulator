#pragma once
#include <string>
#include <unordered_set>

enum class Instruction {
	LDA, LDX, LDY, STA, STX, STY, TAX, TAY, TXA, TYA, TSX, TXS, PHA, PHP,
	PLA, PLP, AND, EOR, ORA, BIT, ADC, SBC, CMP, CPX, CPY, INC, INX, INY,
	DEC, DEX, DEY, ASL, LSR, ROL, ROR, JMP, JSR, RTS, BCC, BCS, BEQ, BMI,
	BNE, BPL, BVC, BVS, CLC, CLD, CLI, CLV, SEC, SED, SEI, BRK, NOP, RTI,
    PRT,
    INVALID
};

enum class AddressMode { // Code:
    ACCUMULATOR,         // A      
    RELATIVE,            // BNE label
    IMMEDIATE,           // #$nn   
                         // #nn    
    ABSOLUTE,            // $nnnn  
    ZERO_PAGE,           // $nn    
    IMPLIED,             // -
    ABS_INDIRECT,        // ($nnnn)
    X_ABSOLUTE,          // $nnnn,X
    Y_ABSOLUTE,          // $nnnn,Y
    X_ZERO_PAGE,         // $nn,X  
    Y_ZERO_PAGE,         // $nn,Y  
    X_INDEX_ZP_INDIRECT, // ($nn,X)
    ZP_INDIRECT_Y_INDEX, // ($nn),Y
    UNKNOWN
};

struct Operation {
    Instruction instruction;
    AddressMode mode;

    bool operator<(const Operation& other) const {
        return std::tie(instruction, mode) < std::tie(other.instruction, other.mode);
    }
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