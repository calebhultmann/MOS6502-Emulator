#include <map>
#include <stdint.h>
#include <string>
#include <unordered_set>
#include <utility>
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
    IMMEDIATE,
    IMMEDIATE_HEX,       // #$nn    | ^#\$[0-9a-fA-F]{2}$
    IMMEDIATE_DEC,       // #nn     | ^#[0-9]{2}$
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

// Instruction and their valid addressing modes
static const map<string, vector<TokenType>> instruction_to_token_types =
{
    {"ADC", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"AND", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"ASL", {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"BCC", {ABSOLUTE_RELATIVE}},
    {"BCS", {ABSOLUTE_RELATIVE}},
    {"BEQ", {ABSOLUTE_RELATIVE}},
    {"BIT", {ZERO_PAGE, ABSOLUTE_RELATIVE}},
    {"BMI", {ABSOLUTE_RELATIVE}},
    {"BNE", {ABSOLUTE_RELATIVE}},
    {"BPL", {ABSOLUTE_RELATIVE}},
    {"BRK", {IMPLIED}},
    {"BVC", {ABSOLUTE_RELATIVE}},
    {"BVS", {ABSOLUTE_RELATIVE}},
    {"CLC", {IMPLIED}},
    {"CLD", {IMPLIED}},
    {"CLI", {IMPLIED}},
    {"CLV", {IMPLIED}},
    {"CMP", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"CPX", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, ABSOLUTE_RELATIVE}},
    {"CPY", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, ABSOLUTE_RELATIVE}},
    {"DEC", {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"DEX", {IMPLIED}},
    {"DEY", {IMPLIED}},
    {"EOR", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"INC", {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"INX", {IMPLIED}},
    {"INY", {IMPLIED}},
    {"JMP", {ABSOLUTE_RELATIVE, ABS_INDIRECT}},
    {"JSR", {ABSOLUTE_RELATIVE}},
    {"LDA", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"LDX", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, Y_ZERO_PAGE, ABSOLUTE_RELATIVE, Y_ABSOLUTE}},
    {"LDY", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"LSR", {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"NOP", {IMPLIED}},
    {"ORA", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"PHA", {IMPLIED}},
    {"PHP", {IMPLIED}},
    {"PLA", {IMPLIED}},
    {"PLP", {IMPLIED}},
    {"ROL", {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"ROR", {ACCUMULATOR, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE}},
    {"RTI", {IMPLIED}},
    {"RTS", {IMPLIED}},
    {"SBC", {IMMEDIATE_DEC, IMMEDIATE_HEX, ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"SEC", {IMPLIED}},
    {"SED", {IMPLIED}},
    {"SEI", {IMPLIED}},
    {"STA", {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE, X_ABSOLUTE, Y_ABSOLUTE, X_INDEX_ZP_INDIRECT, ZP_INDIRECT_Y_INDEX}},
    {"STX", {ZERO_PAGE, Y_ZERO_PAGE, ABSOLUTE_RELATIVE}},
    {"STY", {ZERO_PAGE, X_ZERO_PAGE, ABSOLUTE_RELATIVE}},
    {"TAX", {IMPLIED}},
    {"TAY", {IMPLIED}},
    {"TSX", {IMPLIED}},
    {"TXA", {IMPLIED}},
    {"TXS", {IMPLIED}},
    {"TYA", {IMPLIED}},
};

static const map<pair<string, TokenType>, Byte> instruction_to_opcode =
{
    {{"ADC", IMMEDIATE_DEC}, INS_ADC_IM},
    {{"ADC", IMMEDIATE_HEX}, INS_ADC_IM},
    {{"ADC", ZERO_PAGE}, INS_ADC_ZP},
    {{"ADC", X_ZERO_PAGE}, INS_ADC_ZPX},
    {{"ADC", ABSOLUTE_RELATIVE}, INS_ADC_ABS},
    {{"ADC", X_ABSOLUTE}, INS_ADC_ABS},
    {{"ADC", Y_ABSOLUTE}, INS_ADC_ABSY},
    {{"ADC", X_INDEX_ZP_INDIRECT}, INS_ADC_INDX},
    {{"ADC", ZP_INDIRECT_Y_INDEX}, INS_ADC_INDY},
    {{"AND", IMMEDIATE_DEC}, INS_AND_IM},
    {{"AND", IMMEDIATE_HEX}, INS_AND_IM},
    {{"AND", ZERO_PAGE}, INS_AND_ZP},
    {{"AND", X_ZERO_PAGE}, INS_AND_ZPX},
    {{"AND", ABSOLUTE_RELATIVE}, INS_AND_ABS},
    {{"AND", X_ABSOLUTE}, INS_AND_ABSX},
    {{"AND", Y_ABSOLUTE}, INS_AND_ABSY},
    {{"AND", X_INDEX_ZP_INDIRECT}, INS_AND_INDX},
    {{"AND", ZP_INDIRECT_Y_INDEX}, INS_AND_INDY},
    {{"ASL", ACCUMULATOR}, INS_ASL_ACC},
    {{"ASL", ZERO_PAGE}, INS_ASL_ZP},
    {{"ASL", X_ZERO_PAGE}, INS_ASL_ABSX},
    {{"ASL", ABSOLUTE_RELATIVE}, INS_ASL_ABS},
    {{"BCC", ABSOLUTE_RELATIVE}, INS_BCC},
    {{"BCS", ABSOLUTE_RELATIVE}, INS_BCS},
    {{"BEQ", ABSOLUTE_RELATIVE}, INS_BEQ},
    {{"BIT", ZERO_PAGE}, INS_BIT_ZP},
    {{"BIT", ABSOLUTE_RELATIVE}, INS_BIT_ABS},
    {{"BMI", ABSOLUTE_RELATIVE}, INS_BMI},
    {{"BNE", ABSOLUTE_RELATIVE}, INS_BNE},
    {{"BPL", ABSOLUTE_RELATIVE}, INS_BPL},
    {{"BRK", IMPLIED}, INS_BRK},
    {{"BVS", ABSOLUTE_RELATIVE}, INS_BVS},
    {{"CLC", IMPLIED}, INS_CLC},
    {{"CLD", IMPLIED}, INS_CLD},
    {{"CLI", IMPLIED}, INS_CLI},
    {{"CLV", IMPLIED}, INS_CLV},
    {{"CPX", IMMEDIATE_DEC}, INS_CPX_IM},
    {{"CPX", IMMEDIATE_HEX}, INS_CPX_IM},
    {{"CPX", ZERO_PAGE}, INS_CPX_ZP},
    {{"CPX", ABSOLUTE_RELATIVE}, INS_CPX_ABS},
    {{"CPY", IMMEDIATE_DEC}, INS_CPX_IM},
    {{"CPY", IMMEDIATE_HEX}, INS_CPX_IM},
    {{"CPY", ZERO_PAGE}, INS_CPX_ZP},
    {{"CPY", ABSOLUTE_RELATIVE}, INS_CPX_ABS},
    {{"DEC", ZERO_PAGE}, INS_DEC_ZP},
    {{"DEC", X_ZERO_PAGE}, INS_DEC_ZPX},
    {{"DEC", ABSOLUTE_RELATIVE}, INS_DEC_ABS},
    {{"DEC", X_ABSOLUTE}, INS_DEC_ABSX},
    {{"DEX", IMPLIED}, INS_DEX},
    {{"DEY", IMPLIED}, INS_DEY},
    {{"EOR", IMMEDIATE_DEC}, INS_EOR_IM},
    {{"EOR", IMMEDIATE_HEX}, INS_EOR_IM},
    {{"EOR", ZERO_PAGE}, INS_EOR_ZP},
    {{"EOR", X_ZERO_PAGE}, INS_EOR_ZPX},
    {{"EOR", ABSOLUTE_RELATIVE}, INS_EOR_ABS},
    {{"EOR", X_ABSOLUTE}, INS_EOR_ABSX},
    {{"EOR", Y_ABSOLUTE}, INS_EOR_ABSY},
    {{"EOR", X_INDEX_ZP_INDIRECT}, INS_EOR_INDX},
    {{"EOR", ZP_INDIRECT_Y_INDEX}, INS_EOR_INDY},
    {{"INC", ZERO_PAGE}, INS_INC_ZP},
    {{"INC", X_ZERO_PAGE}, INS_INC_ZPX},
    {{"INC", ABSOLUTE_RELATIVE}, INS_INC_ABS},
    {{"INC", X_ABSOLUTE}, INS_INC_ABSX},
    {{"INX", IMPLIED}, INS_INX},
    {{"INY", IMPLIED}, INS_INY},
    {{"JMP", ABSOLUTE_RELATIVE}, INS_JMP_ABS},
    {{"JMP", ABS_INDIRECT}, INS_JMP_IND},
    {{"JSR", ABSOLUTE_RELATIVE}, INS_JSR_ABS},
    {{"LDA", IMMEDIATE_DEC}, INS_LDA_IM},
    {{"LDA", IMMEDIATE_HEX}, INS_LDA_IM},
    {{"LDA", ZERO_PAGE}, INS_LDA_ZP},
    {{"LDA", X_ZERO_PAGE}, INS_LDA_ZPX},
    {{"LDA", ABSOLUTE_RELATIVE}, INS_LDA_ABS},
    {{"LDA", X_ABSOLUTE}, INS_LDA_ABSX},
    {{"LDA", Y_ABSOLUTE}, INS_LDA_ABSY},
    {{"LDA", X_INDEX_ZP_INDIRECT}, INS_LDA_INDX},
    {{"LDA", ZP_INDIRECT_Y_INDEX}, INS_LDA_INDY},
    {{"LDX", IMMEDIATE_HEX}, INS_LDX_IM},
    {{"LDX", IMMEDIATE_DEC}, INS_LDX_IM},
    {{"LDX", ZERO_PAGE}, INS_LDX_ZP},
    {{"LDX", Y_ZERO_PAGE}, INS_LDX_ZPY},
    {{"LDX", ABSOLUTE_RELATIVE}, INS_LDX_ABS},
    {{"LDX", Y_ABSOLUTE}, INS_LDX_ABSY},
    {{"LDY", IMMEDIATE_HEX}, INS_LDY_IM},
    {{"LDY", IMMEDIATE_DEC}, INS_LDY_IM},
    {{"LDY", ZERO_PAGE}, INS_LDY_ZP},
    {{"LDY", X_ZERO_PAGE}, INS_LDY_ZPX},
    {{"LDY", ABSOLUTE_RELATIVE}, INS_LDY_ABS},
    {{"LDY", X_ABSOLUTE}, INS_LDY_ABSX},
    {{"LSR", ACCUMULATOR}, INS_LSR_ACC},
    {{"LSR", ZERO_PAGE}, INS_LSR_ZP},
    {{"LSR", X_ZERO_PAGE}, INS_LSR_ZPX},
    {{"LSR", ABSOLUTE_RELATIVE}, INS_LSR_ABS},
    {{"LSR", X_ABSOLUTE}, INS_LSR_ABSX},
    {{"NOP", IMPLIED}, INS_NOP},
    {{"ORA", IMMEDIATE_DEC}, INS_ORA_IM},
    {{"ORA", IMMEDIATE_HEX}, INS_ORA_IM},
    {{"ORA", ZERO_PAGE}, INS_ORA_ZP},
    {{"ORA", X_ZERO_PAGE}, INS_ORA_ZPX},
    {{"ORA", ABSOLUTE_RELATIVE}, INS_ORA_ABS},
    {{"ORA", X_ABSOLUTE}, INS_ORA_ABSX},
    {{"ORA", Y_ABSOLUTE}, INS_ORA_ABSY},
    {{"ORA", X_INDEX_ZP_INDIRECT}, INS_ORA_INDX},
    {{"ORA", ZP_INDIRECT_Y_INDEX}, INS_ORA_INDY},
    {{"PHA", IMPLIED}, INS_PHA},
    {{"PHP", IMPLIED}, INS_PHP},
    {{"PLA", IMPLIED}, INS_PLA},
    {{"PLP", IMPLIED}, INS_PLP},
    {{"ROL", ACCUMULATOR}, INS_ROL_ACC},
    {{"ROL", ZERO_PAGE}, INS_ROL_ZP},
    {{"ROL", X_ZERO_PAGE}, INS_ROL_ZPX},
    {{"ROL", ABSOLUTE_RELATIVE}, INS_ROL_ABS},
    {{"ROL", X_ABSOLUTE}, INS_ROL_ABSX},
    {{"ROR", ACCUMULATOR}, INS_ROR_ACC},
    {{"ROR", ZERO_PAGE}, INS_ROR_ZP},
    {{"ROR", X_ZERO_PAGE}, INS_ROR_ZPX},
    {{"ROR", ABSOLUTE_RELATIVE}, INS_ROR_ABS},
    {{"ROR", X_ABSOLUTE}, INS_ROR_ABSX},
    {{"RTI", IMPLIED}, INS_RTI},
    {{"RTS", IMPLIED}, INS_RTS},
    {{"SBC", IMMEDIATE_DEC}, INS_SBC_IM},
    {{"SBC", IMMEDIATE_HEX}, INS_SBC_IM},
    {{"SBC", ZERO_PAGE}, INS_SBC_ZP},
    {{"SBC", X_ZERO_PAGE}, INS_SBC_ZPX},
    {{"SBC", ABSOLUTE_RELATIVE}, INS_SBC_ABS},
    {{"SBC", X_ABSOLUTE}, INS_SBC_ABSX},
    {{"SBC", Y_ABSOLUTE}, INS_SBC_ABSY},
    {{"SBC", X_INDEX_ZP_INDIRECT}, INS_SBC_INDX},
    {{"SBC", ZP_INDIRECT_Y_INDEX}, INS_SBC_INDY},
    {{"SEC", IMPLIED}, INS_SEC},
    {{"SED", IMPLIED}, INS_SED},
    {{"SEI", IMPLIED}, INS_SEI},
    {{"STA", ZERO_PAGE}, INS_STA_ZP},
    {{"STA", X_ZERO_PAGE}, INS_STA_ZPX},
    {{"STA", ABSOLUTE_RELATIVE}, INS_STA_ABS},
    {{"STA", X_ABSOLUTE}, INS_STA_ABSX},
    {{"STA", Y_ABSOLUTE}, INS_STA_ABSY},
    {{"STA", X_INDEX_ZP_INDIRECT}, INS_STA_INDX},
    {{"STA", ZP_INDIRECT_Y_INDEX}, INS_STA_INDY},
    {{"STX", ZERO_PAGE}, INS_STX_ZP},
    {{"STX", Y_ZERO_PAGE}, INS_STX_ZPY},
    {{"STX", ABSOLUTE_RELATIVE}, INS_STX_ABS},
    {{"STY", ZERO_PAGE}, INS_STY_ZP},
    {{"STY", X_ZERO_PAGE}, INS_STY_ZPX},
    {{"STY", ABSOLUTE_RELATIVE}, INS_STY_ABS},
    {{"TAX", IMPLIED}, INS_TAX},
    {{"TAY", IMPLIED}, INS_TAY},
    {{"TSX", IMPLIED}, INS_TSX},
    {{"TXA", IMPLIED}, INS_TXA},
    {{"TXS", IMPLIED}, INS_TXS},
    {{"TYA", IMPLIED}, INS_TYA},
};