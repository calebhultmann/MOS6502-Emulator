#include <cstdint>

// Instruction Opcodes
// 
// Load/Store Operations
    // LDA
static constexpr uint8_t INS_LDA_IM = 0xA9;
static constexpr uint8_t INS_LDA_ZP = 0xA5;
static constexpr uint8_t INS_LDA_ZPX = 0xB5;
static constexpr uint8_t INS_LDA_ABS = 0xAD;
static constexpr uint8_t INS_LDA_ABSX = 0xBD;
static constexpr uint8_t INS_LDA_ABSY = 0xB9;
static constexpr uint8_t INS_LDA_INDX = 0xA1;
static constexpr uint8_t INS_LDA_INDY = 0xB1;
// LDX
static constexpr uint8_t INS_LDX_IM = 0xA2;
static constexpr uint8_t INS_LDX_ZP = 0xA6;
static constexpr uint8_t INS_LDX_ZPY = 0xB6;
static constexpr uint8_t INS_LDX_ABS = 0xAE;
static constexpr uint8_t INS_LDX_ABSY = 0xBE;
// LDY
static constexpr uint8_t INS_LDY_IM = 0xA0;
static constexpr uint8_t INS_LDY_ZP = 0xA4;
static constexpr uint8_t INS_LDY_ZPX = 0xB4;
static constexpr uint8_t INS_LDY_ABS = 0xAC;
static constexpr uint8_t INS_LDY_ABSX = 0xBC;
// STA
static constexpr uint8_t INS_STA_ZP = 0x85;
static constexpr uint8_t INS_STA_ZPX = 0x95;
static constexpr uint8_t INS_STA_ABS = 0x8D;
static constexpr uint8_t INS_STA_ABSX = 0x9D;
static constexpr uint8_t INS_STA_ABSY = 0x99;
static constexpr uint8_t INS_STA_INDX = 0x81;
static constexpr uint8_t INS_STA_INDY = 0x91;
// STX
static constexpr uint8_t INS_STX_ZP = 0x86;
static constexpr uint8_t INS_STX_ZPY = 0x96;
static constexpr uint8_t INS_STX_ABS = 0x8E;
// STY
static constexpr uint8_t INS_STY_ZP = 0x84;
static constexpr uint8_t INS_STY_ZPX = 0x94;
static constexpr uint8_t INS_STY_ABS = 0x8C;

// Register Transfers
    // TAX
static constexpr uint8_t INS_TAX = 0xAA;
// TAY
static constexpr uint8_t INS_TAY = 0xA8;
// TXA
static constexpr uint8_t INS_TXA = 0x8A;
// TYA
static constexpr uint8_t INS_TYA = 0x98;

// Stack Operations
    // TSX
static constexpr uint8_t INS_TSX = 0xBA;
// TXS
static constexpr uint8_t INS_TXS = 0x9A;
// PHA
static constexpr uint8_t INS_PHA = 0x48;
// PHP
static constexpr uint8_t INS_PHP = 0x08;
// PLA
static constexpr uint8_t INS_PLA = 0x68;
// PLP
static constexpr uint8_t INS_PLP = 0x28;

// Logical
    // AND
static constexpr uint8_t INS_AND_IM = 0x29;
static constexpr uint8_t INS_AND_ZP = 0x25;
static constexpr uint8_t INS_AND_ZPX = 0x35;
static constexpr uint8_t INS_AND_ABS = 0x2D;
static constexpr uint8_t INS_AND_ABSX = 0x3D;
static constexpr uint8_t INS_AND_ABSY = 0x39;
static constexpr uint8_t INS_AND_INDX = 0x21;
static constexpr uint8_t INS_AND_INDY = 0x31;
// EOR
static constexpr uint8_t INS_EOR_IM = 0x49;
static constexpr uint8_t INS_EOR_ZP = 0x45;
static constexpr uint8_t INS_EOR_ZPX = 0x55;
static constexpr uint8_t INS_EOR_ABS = 0x4D;
static constexpr uint8_t INS_EOR_ABSX = 0x5D;
static constexpr uint8_t INS_EOR_ABSY = 0x59;
static constexpr uint8_t INS_EOR_INDX = 0x41;
static constexpr uint8_t INS_EOR_INDY = 0x51;
// ORA
static constexpr uint8_t INS_ORA_IM = 0x09;
static constexpr uint8_t INS_ORA_ZP = 0x05;
static constexpr uint8_t INS_ORA_ZPX = 0x15;
static constexpr uint8_t INS_ORA_ABS = 0x0D;
static constexpr uint8_t INS_ORA_ABSX = 0x1D;
static constexpr uint8_t INS_ORA_ABSY = 0x19;
static constexpr uint8_t INS_ORA_INDX = 0x01;
static constexpr uint8_t INS_ORA_INDY = 0x11;
// BIT
static constexpr uint8_t INS_BIT_ZP = 0x24;
static constexpr uint8_t INS_BIT_ABS = 0x2C;

// Arithmetic
    // ADC
static constexpr uint8_t INS_ADC_IM = 0x69;
static constexpr uint8_t INS_ADC_ZP = 0x65;
static constexpr uint8_t INS_ADC_ZPX = 0x75;
static constexpr uint8_t INS_ADC_ABS = 0x6D;
static constexpr uint8_t INS_ADC_ABSX = 0x7D;
static constexpr uint8_t INS_ADC_ABSY = 0x79;
static constexpr uint8_t INS_ADC_INDX = 0x61;
static constexpr uint8_t INS_ADC_INDY = 0x71;
// SBC
static constexpr uint8_t INS_SBC_IM = 0xE9;
static constexpr uint8_t INS_SBC_ZP = 0xE5;
static constexpr uint8_t INS_SBC_ZPX = 0xF5;
static constexpr uint8_t INS_SBC_ABS = 0xED;
static constexpr uint8_t INS_SBC_ABSX = 0xFD;
static constexpr uint8_t INS_SBC_ABSY = 0xF9;
static constexpr uint8_t INS_SBC_INDX = 0xE1;
static constexpr uint8_t INS_SBC_INDY = 0xF1;
// CMP
static constexpr uint8_t INS_CMP_IM = 0xC9;
static constexpr uint8_t INS_CMP_ZP = 0xC5;
static constexpr uint8_t INS_CMP_ZPX = 0xD5;
static constexpr uint8_t INS_CMP_ABS = 0xCD;
static constexpr uint8_t INS_CMP_ABSX = 0xDD;
static constexpr uint8_t INS_CMP_ABSY = 0xD9;
static constexpr uint8_t INS_CMP_INDX = 0xC1;
static constexpr uint8_t INS_CMP_INDY = 0xD1;
// CPX
static constexpr uint8_t INS_CPX_IM = 0xE0;
static constexpr uint8_t INS_CPX_ZP = 0xE4;
static constexpr uint8_t INS_CPX_ABS = 0xEC;
// CPY
static constexpr uint8_t INS_CPY_IM = 0xC0;
static constexpr uint8_t INS_CPY_ZP = 0xC4;
static constexpr uint8_t INS_CPY_ABS = 0xCC;

// Increments & Decrements
    // INC
static constexpr uint8_t INS_INC_ZP = 0xE6;
static constexpr uint8_t INS_INC_ZPX = 0xF6;
static constexpr uint8_t INS_INC_ABS = 0xEE;
static constexpr uint8_t INS_INC_ABSX = 0xFE;
// INX
static constexpr uint8_t INS_INX = 0xE8;
// INY
static constexpr uint8_t INS_INY = 0xC8;
// DEC
static constexpr uint8_t INS_DEC_ZP = 0xC6;
static constexpr uint8_t INS_DEC_ZPX = 0xD6;
static constexpr uint8_t INS_DEC_ABS = 0xCE;
static constexpr uint8_t INS_DEC_ABSX = 0xDE;
// DEX
static constexpr uint8_t INS_DEX = 0xCA;
// DEY
static constexpr uint8_t INS_DEY = 0x88;

// Shifts
    // ASL
static constexpr uint8_t INS_ASL_ACC = 0x0A;
static constexpr uint8_t INS_ASL_ZP = 0x06;
static constexpr uint8_t INS_ASL_ZPX = 0x16;
static constexpr uint8_t INS_ASL_ABS = 0x0E;
static constexpr uint8_t INS_ASL_ABSX = 0x1E;
// LSR
static constexpr uint8_t INS_LSR_ACC = 0x4A;
static constexpr uint8_t INS_LSR_ZP = 0x46;
static constexpr uint8_t INS_LSR_ZPX = 0x56;
static constexpr uint8_t INS_LSR_ABS = 0x4E;
static constexpr uint8_t INS_LSR_ABSX = 0x5E;
// ROL
static constexpr uint8_t INS_ROL_ACC = 0x2A;
static constexpr uint8_t INS_ROL_ZP = 0x26;
static constexpr uint8_t INS_ROL_ZPX = 0x36;
static constexpr uint8_t INS_ROL_ABS = 0x2E;
static constexpr uint8_t INS_ROL_ABSX = 0x3E;
// ROR
static constexpr uint8_t INS_ROR_ACC = 0x6A;
static constexpr uint8_t INS_ROR_ZP = 0x66;
static constexpr uint8_t INS_ROR_ZPX = 0x76;
static constexpr uint8_t INS_ROR_ABS = 0x6E;
static constexpr uint8_t INS_ROR_ABSX = 0x7E;

// Jumps & Calls
    // JMP
static constexpr uint8_t INS_JMP_ABS = 0x4C;
static constexpr uint8_t INS_JMP_IND = 0x6C;
// JSR
static constexpr uint8_t INS_JSR_ABS = 0x20;
// RTS
static constexpr uint8_t INS_RTS = 0x60;

// Branches
static constexpr uint8_t INS_BCC = 0x90;
static constexpr uint8_t INS_BCS = 0xB0;
static constexpr uint8_t INS_BEQ = 0xF0;
static constexpr uint8_t INS_BMI = 0x30;
static constexpr uint8_t INS_BNE = 0xD0;
static constexpr uint8_t INS_BPL = 0x10;
static constexpr uint8_t INS_BVC = 0x50;
static constexpr uint8_t INS_BVS = 0x70;

// Status Flag Changes
static constexpr uint8_t INS_CLC = 0x18;
static constexpr uint8_t INS_CLD = 0xD8;
static constexpr uint8_t INS_CLI = 0x58;
static constexpr uint8_t INS_CLV = 0xB8;
static constexpr uint8_t INS_SEC = 0x38;
static constexpr uint8_t INS_SED = 0xF8;
static constexpr uint8_t INS_SEI = 0x78;

// System Functions
static constexpr uint8_t INS_BRK = 0x00;
static constexpr uint8_t INS_NOP = 0xEA;
static constexpr uint8_t INS_RTI = 0x40;

// Custom Opcodes
static constexpr uint8_t INS_PRT = 0x80;