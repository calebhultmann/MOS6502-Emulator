#include <stdint.h>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using Byte = uint8_t;


// Instruction Opcodes
// 51 codes left

static constexpr Byte INS_ADC_IM = 0x69; // Not Implemented
static constexpr Byte INS_ADC_ZP = 0x65; // Not Implemented
static constexpr Byte INS_ADC_ZPX = 0x75; // Not Implemented
static constexpr Byte INS_ADC_ABS = 0x6D; // Not Implemented
static constexpr Byte INS_ADC_ABSX = 0x7D; // Not Implemented
static constexpr Byte INS_ADC_ABSY = 0x79; // Not Implemented
static constexpr Byte INS_ADC_INDX = 0x61; // Not Implemented
static constexpr Byte INS_ADC_INDY = 0x71; // Not Implemented
static constexpr Byte INS_AND_IM = 0x29;
static constexpr Byte INS_AND_ZP = 0x25;
static constexpr Byte INS_AND_ZPX = 0x35;
static constexpr Byte INS_AND_ABS = 0x2D;
static constexpr Byte INS_AND_ABSX = 0x3D;
static constexpr Byte INS_AND_ABSY = 0x39;
static constexpr Byte INS_AND_INDX = 0x21; // Not Implemented
static constexpr Byte INS_AND_INDY = 0x31; // Not Implemented
static constexpr Byte INS_ASL_ACC = 0x0A;
static constexpr Byte INS_ASL_ZP = 0x06;
static constexpr Byte INS_ASL_ZPX = 0x16;
static constexpr Byte INS_ASL_ABS = 0x0E;
static constexpr Byte INS_ASL_ABSX = 0x1E;
static constexpr Byte INS_BCC = 0x90;
static constexpr Byte INS_BCS = 0xB0;
static constexpr Byte INS_BEQ = 0xF0;
static constexpr Byte INS_BIT_ZP = 0x24;
static constexpr Byte INS_BIT_ABS = 0x2C;
static constexpr Byte INS_BMI = 0x30;
static constexpr Byte INS_BNE = 0xD0;
static constexpr Byte INS_BPL = 0x10;
static constexpr Byte INS_BRK = 0x00; // Not Implemented
static constexpr Byte INS_BVC = 0x50;
static constexpr Byte INS_BVS = 0x70;
static constexpr Byte INS_CLC = 0x18;
static constexpr Byte INS_CLD = 0xD8;
static constexpr Byte INS_CLI = 0x58;
static constexpr Byte INS_CLV = 0xB8;
static constexpr Byte INS_CMP_IM = 0xC9; // Not Implemented
static constexpr Byte INS_CMP_ZP = 0xC5; // Not Implemented
static constexpr Byte INS_CMP_ZPX = 0xD5; // Not Implemented
static constexpr Byte INS_CMP_ABS = 0xCD; // Not Implemented
static constexpr Byte INS_CMP_ABSX = 0xDD; // Not Implemented
static constexpr Byte INS_CMP_ABSY = 0xD9; // Not Implemented
static constexpr Byte INS_CMP_INDX = 0xC1; // Not Implemented
static constexpr Byte INS_CMP_INDY = 0xD1; // Not Implemented
static constexpr Byte INS_CPX_IM = 0xE0; // Not Implemented
static constexpr Byte INS_CPX_ZP = 0xE4; // Not Implemented
static constexpr Byte INS_CPX_ABS = 0xEC; // Not Implemented
static constexpr Byte INS_CPY_IM = 0xC0; // Not Implemented
static constexpr Byte INS_CPY_ZP = 0xC4; // Not Implemented
static constexpr Byte INS_CPY_ABS = 0xCC; // Not Implemented
static constexpr Byte INS_DEC_ZP = 0xC6;
static constexpr Byte INS_DEC_ZPX = 0xD6;
static constexpr Byte INS_DEC_ABS = 0xCE;
static constexpr Byte INS_DEC_ABSX = 0xDE;
static constexpr Byte INS_DEX = 0xCA;
static constexpr Byte INS_DEY = 0x88;
static constexpr Byte INS_EOR_IM = 0x49;
static constexpr Byte INS_EOR_ZP = 0x45;
static constexpr Byte INS_EOR_ZPX = 0x55;
static constexpr Byte INS_EOR_ABS = 0x4D;
static constexpr Byte INS_EOR_ABSX = 0x5D;
static constexpr Byte INS_EOR_ABSY = 0x59;
static constexpr Byte INS_EOR_INDX = 0x41; // Not Implemented
static constexpr Byte INS_EOR_INDY = 0x51; // Not Implemented
static constexpr Byte INS_INC_ZP = 0xE6;
static constexpr Byte INS_INC_ZPX = 0xF6;
static constexpr Byte INS_INC_ABS = 0xEE;
static constexpr Byte INS_INC_ABSX = 0xFE;
static constexpr Byte INS_INX = 0xE8;
static constexpr Byte INS_INY = 0xC8;
static constexpr Byte INS_JMP_ABS = 0x4C; // Not Implemented
static constexpr Byte INS_JMP_IND = 0x6C; // Not Implemented
static constexpr Byte INS_JSR_ABS = 0x20; // Not Implemented
static constexpr Byte INS_LDA_IM = 0xA9;
static constexpr Byte INS_LDA_ZP = 0xA5;
static constexpr Byte INS_LDA_ZPX = 0xB5;
static constexpr Byte INS_LDA_ABS = 0xAD;
static constexpr Byte INS_LDA_ABSX = 0xBD;
static constexpr Byte INS_LDA_ABSY = 0xB9;
static constexpr Byte INS_LDA_INDX = 0xA1;
static constexpr Byte INS_LDA_INDY = 0xB1;
static constexpr Byte INS_LDX_IM = 0xA2;
static constexpr Byte INS_LDX_ZP = 0xA6;
static constexpr Byte INS_LDX_ZPY = 0xB6;
static constexpr Byte INS_LDX_ABS = 0xAE;
static constexpr Byte INS_LDX_ABSY = 0xBE;
static constexpr Byte INS_LDY_IM = 0xA0;
static constexpr Byte INS_LDY_ZP = 0xA4;
static constexpr Byte INS_LDY_ZPX = 0xB4;
static constexpr Byte INS_LDY_ABS = 0xAC;
static constexpr Byte INS_LDY_ABSX = 0xBC;
static constexpr Byte INS_LSR_ACC = 0x4A;
static constexpr Byte INS_LSR_ZP = 0x46;
static constexpr Byte INS_LSR_ZPX = 0x56;
static constexpr Byte INS_LSR_ABS = 0x4E;
static constexpr Byte INS_LSR_ABSX = 0x5E;
static constexpr Byte INS_NOP = 0xEA;
static constexpr Byte INS_ORA_IM = 0x09;
static constexpr Byte INS_ORA_ZP = 0x05;
static constexpr Byte INS_ORA_ZPX = 0x15;
static constexpr Byte INS_ORA_ABS = 0x0D;
static constexpr Byte INS_ORA_ABSX = 0x1D;
static constexpr Byte INS_ORA_ABSY = 0x19;
static constexpr Byte INS_ORA_INDX = 0x01; // Not Implemented
static constexpr Byte INS_ORA_INDY = 0x11; // Not Implemented
static constexpr Byte INS_PHA = 0x48; // Not Implemented
static constexpr Byte INS_PHP = 0x08; // Not Implemented
static constexpr Byte INS_PLA = 0x68; // Not Implemented
static constexpr Byte INS_PLP = 0x28; // Not Implemented
static constexpr Byte INS_ROL_ACC = 0x2A; // Not Implemented
static constexpr Byte INS_ROL_ZP = 0x26; // Not Implemented
static constexpr Byte INS_ROL_ZPX = 0x36; // Not Implemented
static constexpr Byte INS_ROL_ABS = 0x2E; // Not Implemented
static constexpr Byte INS_ROL_ABSX = 0x3E; // Not Implemented
static constexpr Byte INS_ROR_ACC = 0x6A; // Not Implemented
static constexpr Byte INS_ROR_ZP = 0x66; // Not Implemented
static constexpr Byte INS_ROR_ZPX = 0x76; // Not Implemented
static constexpr Byte INS_ROR_ABS = 0x6E; // Not Implemented
static constexpr Byte INS_ROR_ABSX = 0x7E; // Not Implemented
static constexpr Byte INS_RTI = 0x40; // Not Implemented
static constexpr Byte INS_RTS = 0x60; // Not Implemented
static constexpr Byte INS_SBC_IM = 0xE9; // Not Implemented
static constexpr Byte INS_SBC_ZP = 0xE5; // Not Implemented
static constexpr Byte INS_SBC_ZPX = 0xF5; // Not Implemented
static constexpr Byte INS_SBC_ABS = 0xED; // Not Implemented
static constexpr Byte INS_SBC_ABSX = 0xFD; // Not Implemented
static constexpr Byte INS_SBC_ABSY = 0xF9; // Not Implemented
static constexpr Byte INS_SBC_INDX = 0xE1; // Not Implemented
static constexpr Byte INS_SBC_INDY = 0xF1; // Not Implemented
static constexpr Byte INS_SEC = 0x38;
static constexpr Byte INS_SED = 0xF8;
static constexpr Byte INS_SEI = 0x78;
static constexpr Byte INS_STA_ZP = 0x85;
static constexpr Byte INS_STA_ZPX = 0x95;
static constexpr Byte INS_STA_ABS = 0x8D;
static constexpr Byte INS_STA_ABSX = 0x9D;
static constexpr Byte INS_STA_ABSY = 0x99;
static constexpr Byte INS_STA_INDX = 0x81; // Not Implemented
static constexpr Byte INS_STA_INDY = 0x91; // Not Implemented
static constexpr Byte INS_STX_ZP = 0x86;
static constexpr Byte INS_STX_ZPY = 0x96;
static constexpr Byte INS_STX_ABS = 0x8E;
static constexpr Byte INS_STY_ZP = 0x84;
static constexpr Byte INS_STY_ZPX = 0x94;
static constexpr Byte INS_STY_ABS = 0x8C;
static constexpr Byte INS_TAX = 0xAA;
static constexpr Byte INS_TAY = 0xA8;
static constexpr Byte INS_TSX = 0xBA; // Not Implemented
static constexpr Byte INS_TXA = 0x8A;
static constexpr Byte INS_TXS = 0x9A; // Not Implemented
static constexpr Byte INS_TYA = 0x98;

// Instructions
static const unordered_set<string> valid_instructions =
{ "LDA", "LDX", "LDY", "STA", "STX", "STY", "TAX", "TAY", "TSX", "TXA", "TXS", "TYA", "PHA", "PHP",
  "PLA", "PLP", "ASL", "LSR", "ROL", "ROR", "AND", "BIT", "EOR", "ORA", "ADC", "CMP", "CPX", "CPY",
  "SBC", "DEC", "DEX", "DEY", "INC", "INX", "INY", "BRK", "JMP", "JSR", "RTI", "RTS", "BCC", "BCS",
  "BEQ", "BMI", "BNE", "BPL", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "SEC", "SED", "SEI", "NOP" };

// Address Modes
enum TokenType {
    LABEL,
    LABELREF,
    OPCODE,              // Hex:    | Regex:
    IMPLIED,             // N/A     | N/A          ** How to use? **
    ACCUMULATOR,         // A       | ^A$
    IMMEDIATE,           // #$nn    | ^#\$[0-9a-fA-F]{2}$
                         // #nn     | ^#[0-9]{2}$
    ABSOLUTE_RELATIVE,   // $nnnn   | ^\$[0-9a-fA-F]{4}$   Note: this token is relative when used for branch instructions, and absolute otherwise 
    X_ABSOLUTE,          // $nnnn,X | ^\$[0-9a-fA-F]{4},X$
    Y_ABSOLUTE,          // $nnnn,Y | ^\$[0-9a-fA-F]{4},Y$
    ABS_INDIRECT,        // ($nnnn) | ^\(\$[0-9a-fA-F]{4}\)$
    ZERO_PAGE,           // $nn     | ^\$[0-9a-fA-F]{2}$
    X_ZERO_PAGE,         // $nn,X   | ^\$[0-9a-fA-F]{2},X$
    Y_ZERO_PAGE,         // $nn,Y   | ^\$[0-9a-fA-F]{2},Y$
    X_INDEX_ZP_INDIRECT, // ($nn,X) | ^\(\$[0-9a-fA-F]{2},X\)$
    ZP_INDIRECT_Y_INDEX, // ($nn),Y | ^\(\$[0-9a-fA-F]{2}\),Y$
    UNKNOWN
};

struct Token {
    TokenType type;
    string value;
};