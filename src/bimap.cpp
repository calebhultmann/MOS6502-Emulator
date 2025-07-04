#include "bimap.h"
#include <utility>

using namespace std;
using Byte = uint8_t;

//instruction_opcode_map

template<typename Bimap, typename L, typename R>
void insert_pair(Bimap& bm, L&& left, R&& right) {
    bm.insert(typename Bimap::value_type(std::forward<L>(left), std::forward<R>(right)));
}

const boost::bimap<Operation, Byte>& construct_bimap() {
	static const boost::bimap<Operation, Byte> bimap = [] {
		boost::bimap< Operation, Byte> bm;
		// Load/Store Operations
            // LDA
        insert_pair(bm, Operation{ Instruction::LDA, IMMEDIATE }, INS_LDA_IM);
        insert_pair(bm, Operation{ Instruction::LDA, ZERO_PAGE }, INS_LDA_ZP);
        insert_pair(bm, Operation{ Instruction::LDA, X_ZERO_PAGE }, INS_LDA_ZPX);
        insert_pair(bm, Operation{ Instruction::LDA, ABSOLUTE }, INS_LDA_ABS);
        insert_pair(bm, Operation{ Instruction::LDA, X_ABSOLUTE }, INS_LDA_ABSX);
        insert_pair(bm, Operation{ Instruction::LDA, Y_ABSOLUTE }, INS_LDA_ABSY);
        insert_pair(bm, Operation{ Instruction::LDA, X_INDEX_ZP_INDIRECT }, INS_LDA_INDX);
        insert_pair(bm, Operation{ Instruction::LDA, ZP_INDIRECT_Y_INDEX }, INS_LDA_INDY);

            // LDX
        insert_pair(bm, Operation{ Instruction::LDX, IMMEDIATE }, INS_LDX_IM);
        insert_pair(bm, Operation{ Instruction::LDX, ZERO_PAGE }, INS_LDX_ZP);
        insert_pair(bm, Operation{ Instruction::LDX, Y_ZERO_PAGE }, INS_LDX_ZPY);
        insert_pair(bm, Operation{ Instruction::LDX, ABSOLUTE }, INS_LDX_ABS);
        insert_pair(bm, Operation{ Instruction::LDX, Y_ABSOLUTE }, INS_LDX_ABSY);

            // LDY
        insert_pair(bm, Operation{ Instruction::LDY, IMMEDIATE }, INS_LDY_IM);
        insert_pair(bm, Operation{ Instruction::LDY, ZERO_PAGE }, INS_LDY_ZP);
        insert_pair(bm, Operation{ Instruction::LDY, X_ZERO_PAGE }, INS_LDY_ZPX);
        insert_pair(bm, Operation{ Instruction::LDY, ABSOLUTE }, INS_LDY_ABS);
        insert_pair(bm, Operation{ Instruction::LDY, X_ABSOLUTE }, INS_LDY_ABSX);

            // STA
        insert_pair(bm, Operation{ Instruction::STA, ZERO_PAGE }, INS_STA_ZP);
        insert_pair(bm, Operation{ Instruction::STA, X_ZERO_PAGE }, INS_STA_ZPX);
        insert_pair(bm, Operation{ Instruction::STA, ABSOLUTE }, INS_STA_ABS);
        insert_pair(bm, Operation{ Instruction::STA, X_ABSOLUTE }, INS_STA_ABSX);
        insert_pair(bm, Operation{ Instruction::STA, Y_ABSOLUTE }, INS_STA_ABSY);
        insert_pair(bm, Operation{ Instruction::STA, X_INDEX_ZP_INDIRECT }, INS_STA_INDX);
        insert_pair(bm, Operation{ Instruction::STA, ZP_INDIRECT_Y_INDEX }, INS_STA_INDY);

            // STX
        insert_pair(bm, Operation{ Instruction::STX, ZERO_PAGE }, INS_STX_ZP);
        insert_pair(bm, Operation{ Instruction::STX, Y_ZERO_PAGE }, INS_STX_ZPY);
        insert_pair(bm, Operation{ Instruction::STX, ABSOLUTE }, INS_STX_ABS);

            // STY
        insert_pair(bm, Operation{ Instruction::STY, ZERO_PAGE }, INS_STY_ZP);
        insert_pair(bm, Operation{ Instruction::STY, X_ZERO_PAGE }, INS_STY_ZPX);
        insert_pair(bm, Operation{ Instruction::STY, ABSOLUTE }, INS_STY_ABS);

        // Register Transfers
		    // TAX
        insert_pair(bm, Operation{ Instruction::TAX, IMPLIED }, INS_TAX);

            // TAY
        insert_pair(bm, Operation{ Instruction::TAY, IMPLIED }, INS_TAY);

            // TXA
        insert_pair(bm, Operation{ Instruction::TXA, IMPLIED }, INS_TXA);

            // TYA
        insert_pair(bm, Operation{ Instruction::TYA,  IMPLIED }, INS_TYA);

		// Stack Operations
            // TSX
        insert_pair(bm, Operation{ Instruction::TSX, IMPLIED }, INS_TSX);

            // TXS
        insert_pair(bm, Operation{ Instruction::TXS, IMPLIED }, INS_TXS);

            // PHA
        insert_pair(bm, Operation{ Instruction::PHA, IMPLIED }, INS_PHA);

            // PHP
        insert_pair(bm, Operation{ Instruction::PHP, IMPLIED }, INS_PHP);

            // PLA
        insert_pair(bm, Operation{ Instruction::PLA, IMPLIED }, INS_PLA);

            // PLP
        insert_pair(bm, Operation{ Instruction::PLP, IMPLIED }, INS_PLP);

        // Logical
            // AND
        insert_pair(bm, Operation{ Instruction::AND, IMMEDIATE }, INS_AND_IM);
        insert_pair(bm, Operation{ Instruction::AND, ZERO_PAGE }, INS_AND_ZP);
        insert_pair(bm, Operation{ Instruction::AND, X_ZERO_PAGE }, INS_AND_ZPX);
        insert_pair(bm, Operation{ Instruction::AND, ABSOLUTE }, INS_AND_ABS);
        insert_pair(bm, Operation{ Instruction::AND, X_ABSOLUTE }, INS_AND_ABSX);
        insert_pair(bm, Operation{ Instruction::AND, Y_ABSOLUTE }, INS_AND_ABSY);
        insert_pair(bm, Operation{ Instruction::AND, X_INDEX_ZP_INDIRECT }, INS_AND_INDX);
        insert_pair(bm, Operation{ Instruction::AND, ZP_INDIRECT_Y_INDEX }, INS_AND_INDY);

            // EOR
        insert_pair(bm, Operation{ Instruction::EOR, IMMEDIATE }, INS_EOR_IM);
        insert_pair(bm, Operation{ Instruction::EOR, ZERO_PAGE }, INS_EOR_ZP);
        insert_pair(bm, Operation{ Instruction::EOR, X_ZERO_PAGE }, INS_EOR_ZPX);
        insert_pair(bm, Operation{ Instruction::EOR, ABSOLUTE }, INS_EOR_ABS);
        insert_pair(bm, Operation{ Instruction::EOR, X_ABSOLUTE }, INS_EOR_ABSX);
        insert_pair(bm, Operation{ Instruction::EOR, Y_ABSOLUTE }, INS_EOR_ABSY);
        insert_pair(bm, Operation{ Instruction::EOR, X_INDEX_ZP_INDIRECT }, INS_EOR_INDX);
        insert_pair(bm, Operation{ Instruction::EOR, ZP_INDIRECT_Y_INDEX }, INS_EOR_INDY);

            // ORA
        insert_pair(bm, Operation{ Instruction::ORA, IMMEDIATE }, INS_ORA_IM);
        insert_pair(bm, Operation{ Instruction::ORA, ZERO_PAGE }, INS_ORA_ZP);
        insert_pair(bm, Operation{ Instruction::ORA, X_ZERO_PAGE }, INS_ORA_ZPX);
        insert_pair(bm, Operation{ Instruction::ORA, ABSOLUTE }, INS_ORA_ABS);
        insert_pair(bm, Operation{ Instruction::ORA, X_ABSOLUTE }, INS_ORA_ABSX);
        insert_pair(bm, Operation{ Instruction::ORA, Y_ABSOLUTE }, INS_ORA_ABSY);
        insert_pair(bm, Operation{ Instruction::ORA, X_INDEX_ZP_INDIRECT }, INS_ORA_INDX);
        insert_pair(bm, Operation{ Instruction::ORA, ZP_INDIRECT_Y_INDEX }, INS_ORA_INDY);

            // BIT
        insert_pair(bm, Operation{ Instruction::BIT, ZERO_PAGE }, INS_BIT_ZP);
        insert_pair(bm, Operation{ Instruction::BIT, ABSOLUTE }, INS_BIT_ABS);

		// Arithmetic
		    // ADC
		insert_pair(bm, Operation{ Instruction::ADC, IMMEDIATE }, INS_ADC_IM);
		insert_pair(bm, Operation{ Instruction::ADC, ZERO_PAGE }, INS_ADC_ZP);
		insert_pair(bm, Operation{ Instruction::ADC, X_ZERO_PAGE }, INS_ADC_ZPX);
		insert_pair(bm, Operation{ Instruction::ADC, ABSOLUTE }, INS_ADC_ABS);
		insert_pair(bm, Operation{ Instruction::ADC, X_ABSOLUTE }, INS_ADC_ABSX);
		insert_pair(bm, Operation{ Instruction::ADC, Y_ABSOLUTE }, INS_ADC_ABSY);
		insert_pair(bm, Operation{ Instruction::ADC, X_INDEX_ZP_INDIRECT }, INS_ADC_INDX);
		insert_pair(bm, Operation{ Instruction::ADC, ZP_INDIRECT_Y_INDEX }, INS_ADC_INDY);

            // SBC
        insert_pair(bm, Operation{ Instruction::SBC, IMMEDIATE }, INS_SBC_IM);
        insert_pair(bm, Operation{ Instruction::SBC, ZERO_PAGE }, INS_SBC_ZP);
        insert_pair(bm, Operation{ Instruction::SBC, X_ZERO_PAGE }, INS_SBC_ZPX);
        insert_pair(bm, Operation{ Instruction::SBC, ABSOLUTE }, INS_SBC_ABS);
        insert_pair(bm, Operation{ Instruction::SBC, X_ABSOLUTE }, INS_SBC_ABSX);
        insert_pair(bm, Operation{ Instruction::SBC, Y_ABSOLUTE }, INS_SBC_ABSY);
        insert_pair(bm, Operation{ Instruction::SBC, X_INDEX_ZP_INDIRECT }, INS_SBC_INDX);
        insert_pair(bm, Operation{ Instruction::SBC, ZP_INDIRECT_Y_INDEX }, INS_SBC_INDY);

            // CMP
        insert_pair(bm, Operation{ Instruction::CMP, IMMEDIATE }, INS_CMP_IM);
        insert_pair(bm, Operation{ Instruction::CMP, ZERO_PAGE }, INS_CMP_ZP);
        insert_pair(bm, Operation{ Instruction::CMP, X_ZERO_PAGE }, INS_CMP_ZPX);
        insert_pair(bm, Operation{ Instruction::CMP, ABSOLUTE }, INS_CMP_ABS);
        insert_pair(bm, Operation{ Instruction::CMP, X_ABSOLUTE }, INS_CMP_ABSX);
        insert_pair(bm, Operation{ Instruction::CMP, Y_ABSOLUTE }, INS_CMP_ABSY);
        insert_pair(bm, Operation{ Instruction::CMP, X_INDEX_ZP_INDIRECT }, INS_CMP_INDX);
        insert_pair(bm, Operation{ Instruction::CMP, ZP_INDIRECT_Y_INDEX }, INS_CMP_INDY);

            // CPX
        insert_pair(bm, Operation{ Instruction::CPX, IMMEDIATE }, INS_CPX_IM);
        insert_pair(bm, Operation{ Instruction::CPX, ZERO_PAGE }, INS_CPX_ZP);
        insert_pair(bm, Operation{ Instruction::CPX, ABSOLUTE }, INS_CPX_ABS);

            // CPY
        insert_pair(bm, Operation{ Instruction::CPY, IMMEDIATE }, INS_CPY_IM);
        insert_pair(bm, Operation{ Instruction::CPY, ZERO_PAGE }, INS_CPY_ZP);
        insert_pair(bm, Operation{ Instruction::CPY, ABSOLUTE }, INS_CPY_ABS);

		// Increments & Decrements
            // INC
        insert_pair(bm, Operation{ Instruction::INC, ZERO_PAGE }, INS_INC_ZP);
        insert_pair(bm, Operation{ Instruction::INC, X_ZERO_PAGE }, INS_INC_ZPX);
        insert_pair(bm, Operation{ Instruction::INC, ABSOLUTE }, INS_INC_ABS);
        insert_pair(bm, Operation{ Instruction::INC, X_ABSOLUTE }, INS_INC_ABSX);

            // INX
        insert_pair(bm, Operation{ Instruction::INX, IMPLIED }, INS_INX);
        
            // INY
        insert_pair(bm, Operation{ Instruction::INY, IMPLIED }, INS_INY);

            // DEC
        insert_pair(bm, Operation{ Instruction::DEC, ZERO_PAGE }, INS_DEC_ZP);
        insert_pair(bm, Operation{ Instruction::DEC, X_ZERO_PAGE }, INS_DEC_ZPX);
        insert_pair(bm, Operation{ Instruction::DEC, ABSOLUTE }, INS_DEC_ABS);
        insert_pair(bm, Operation{ Instruction::DEC, X_ABSOLUTE }, INS_DEC_ABSX);

            // DEX
        insert_pair(bm, Operation{ Instruction::DEX, IMPLIED }, INS_DEX);

            // DEY
        insert_pair(bm, Operation{ Instruction::DEY, IMPLIED }, INS_DEY);

        // Shifts
            // ASL
		insert_pair(bm, Operation{ Instruction::ASL, ACCUMULATOR }, INS_ASL_ACC);
		insert_pair(bm, Operation{ Instruction::ASL, ZERO_PAGE }, INS_ASL_ZP);
		insert_pair(bm, Operation{ Instruction::ASL, X_ZERO_PAGE }, INS_ASL_ZPX);
		insert_pair(bm, Operation{ Instruction::ASL, ABSOLUTE }, INS_ASL_ABS);
		insert_pair(bm, Operation{ Instruction::ASL, X_ABSOLUTE }, INS_ASL_ABSX);

            // LSR
        insert_pair(bm, Operation{ Instruction::LSR, ACCUMULATOR }, INS_LSR_ACC);
        insert_pair(bm, Operation{ Instruction::LSR, ZERO_PAGE }, INS_LSR_ZP);
        insert_pair(bm, Operation{ Instruction::LSR, X_ZERO_PAGE }, INS_LSR_ZPX);
        insert_pair(bm, Operation{ Instruction::LSR, ABSOLUTE }, INS_LSR_ABS);
        insert_pair(bm, Operation{ Instruction::LSR, X_ABSOLUTE }, INS_LSR_ABSX);

            // ROL
        insert_pair(bm, Operation{ Instruction::ROL, ACCUMULATOR }, INS_ROL_ACC);
        insert_pair(bm, Operation{ Instruction::ROL, ZERO_PAGE }, INS_ROL_ZP);
        insert_pair(bm, Operation{ Instruction::ROL, X_ZERO_PAGE }, INS_ROL_ZPX);
        insert_pair(bm, Operation{ Instruction::ROL, ABSOLUTE }, INS_ROL_ABS);
        insert_pair(bm, Operation{ Instruction::ROL, X_ABSOLUTE }, INS_ROL_ABSX);

            // ROR
        insert_pair(bm, Operation{ Instruction::ROR, ACCUMULATOR }, INS_ROR_ACC);
        insert_pair(bm, Operation{ Instruction::ROR, ZERO_PAGE }, INS_ROR_ZP);
        insert_pair(bm, Operation{ Instruction::ROR, X_ZERO_PAGE }, INS_ROR_ZPX);
        insert_pair(bm, Operation{ Instruction::ROR, ABSOLUTE }, INS_ROR_ABS);
        insert_pair(bm, Operation{ Instruction::ROR, X_ABSOLUTE }, INS_ROR_ABSX);

        // Jumps & Calls
            // JMP
        insert_pair(bm, Operation{ Instruction::JMP, ABSOLUTE }, INS_JMP_ABS);
        insert_pair(bm, Operation{ Instruction::JMP, ABS_INDIRECT }, INS_JMP_IND);

            // JSR
        insert_pair(bm, Operation{ Instruction::JSR, ABSOLUTE }, INS_JSR_ABS);

            // RTS
        insert_pair(bm, Operation{ Instruction::RTS, IMPLIED }, INS_RTS);

        // Branches
		insert_pair(bm, Operation{ Instruction::BCC, RELATIVE }, INS_BCC);
		insert_pair(bm, Operation{ Instruction::BCS, RELATIVE }, INS_BCS);
		insert_pair(bm, Operation{ Instruction::BEQ, RELATIVE }, INS_BEQ);
		insert_pair(bm, Operation{ Instruction::BMI, RELATIVE }, INS_BMI);
		insert_pair(bm, Operation{ Instruction::BNE, RELATIVE }, INS_BNE);
		insert_pair(bm, Operation{ Instruction::BPL, RELATIVE }, INS_BPL);
        insert_pair(bm, Operation{ Instruction::BVC, RELATIVE }, INS_BVC);
        insert_pair(bm, Operation{ Instruction::BVS, RELATIVE }, INS_BVS);

        // Status Flag Changes
        insert_pair(bm, Operation{ Instruction::CLC, IMPLIED }, INS_CLC);
        insert_pair(bm, Operation{ Instruction::CLD, IMPLIED }, INS_CLD);
        insert_pair(bm, Operation{ Instruction::CLI, IMPLIED }, INS_CLI);
        insert_pair(bm, Operation{ Instruction::CLV, IMPLIED }, INS_CLV);
        insert_pair(bm, Operation{ Instruction::SEC, IMPLIED }, INS_SEC);
        insert_pair(bm, Operation{ Instruction::SED, IMPLIED }, INS_SED);
        insert_pair(bm, Operation{ Instruction::SEI, IMPLIED }, INS_SEI);

        // System Functions
        insert_pair(bm, Operation{ Instruction::BRK, IMPLIED  }, INS_BRK);
        insert_pair(bm, Operation{ Instruction::NOP, IMPLIED }, INS_NOP);
        insert_pair(bm, Operation{ Instruction::RTI, IMPLIED }, INS_RTI);

        return bm;
    }();
	return bimap;
}