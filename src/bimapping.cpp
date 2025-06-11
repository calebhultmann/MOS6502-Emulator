#include "abstraction.h"

const boost::bimap< pair<string, TokenType>, Byte>& construct_bimap() {
	static const boost::bimap< pair<string, TokenType>, Byte> bimap = [] {
		boost::bimap< pair<string, TokenType>, Byte> bm;
		bm.insert({ {"ADC", IMMEDIATE_DEC}, INS_ADC_IM });
		bm.insert({ {"ADC", IMMEDIATE_HEX}, INS_ADC_IM });
		bm.insert({ {"ADC", ZERO_PAGE}, INS_ADC_ZP });
		bm.insert({ {"ADC", X_ZERO_PAGE}, INS_ADC_ZPX });
		bm.insert({ {"ADC", ABSOLUTE_RELATIVE}, INS_ADC_ABS });
		bm.insert({ {"ADC", X_ABSOLUTE}, INS_ADC_ABS });
		bm.insert({ {"ADC", Y_ABSOLUTE}, INS_ADC_ABSY });
		bm.insert({ {"ADC", X_INDEX_ZP_INDIRECT}, INS_ADC_INDX });
		bm.insert({ {"ADC", ZP_INDIRECT_Y_INDEX}, INS_ADC_INDY });
		bm.insert({ {"AND", IMMEDIATE_DEC}, INS_AND_IM });
		bm.insert({ {"AND", IMMEDIATE_HEX}, INS_AND_IM });
		bm.insert({ {"AND", ZERO_PAGE}, INS_AND_ZP });
		bm.insert({ {"AND", X_ZERO_PAGE}, INS_AND_ZPX });
		bm.insert({ {"AND", ABSOLUTE_RELATIVE}, INS_AND_ABS });
		bm.insert({ {"AND", X_ABSOLUTE}, INS_AND_ABSX });
		bm.insert({ {"AND", Y_ABSOLUTE}, INS_AND_ABSY });
		bm.insert({ {"AND", X_INDEX_ZP_INDIRECT}, INS_AND_INDX });
		bm.insert({ {"AND", ZP_INDIRECT_Y_INDEX}, INS_AND_INDY });
		bm.insert({ {"ASL", ACCUMULATOR}, INS_ASL_ACC });
		bm.insert({ {"ASL", ZERO_PAGE}, INS_ASL_ZP });
		bm.insert({ {"ASL", X_ZERO_PAGE}, INS_ASL_ABSX });
		bm.insert({ {"ASL", ABSOLUTE_RELATIVE}, INS_ASL_ABS });
		bm.insert({ {"BCC", ABSOLUTE_RELATIVE}, INS_BCC });
		bm.insert({ {"BCS", ABSOLUTE_RELATIVE}, INS_BCS });
		bm.insert({ {"BEQ", ABSOLUTE_RELATIVE}, INS_BEQ });
		bm.insert({ {"BIT", ZERO_PAGE}, INS_BIT_ZP });
		bm.insert({ {"BIT", ABSOLUTE_RELATIVE}, INS_BIT_ABS });
		bm.insert({ {"BMI", ABSOLUTE_RELATIVE}, INS_BMI });
		bm.insert({ {"BNE", ABSOLUTE_RELATIVE}, INS_BNE });
		bm.insert({ {"BPL", ABSOLUTE_RELATIVE}, INS_BPL });
	}();
}