#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      BCC                                                                                              BCC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BCC_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0x150] = INS_BCC;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BCC_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BCC;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BCC_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;

	// Initialize memory
	system.rom[0x1F0] = INS_BCC;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BCC_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BCC;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BCC_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;

	// Initialize memory
	system.rom[0x110] = INS_BCC;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BCS                                                                                              BCS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BCS_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BCS;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BCS_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0x150] = INS_BCS;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BCS_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0x1F0] = INS_BCS;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BCS_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0x150] = INS_BCS;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BCS_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0x110] = INS_BCS;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BEQ                                                                                              BEQ      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BEQ_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BEQ;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BEQ_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0x150] = INS_BEQ;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BEQ_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0x1F0] = INS_BEQ;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BEQ_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0x150] = INS_BEQ;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BEQ_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0x110] = INS_BEQ;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BMI                                                                                              BMI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BMI_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BMI;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BMI_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0x150] = INS_BMI;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BMI_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0x1F0] = INS_BMI;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BMI_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0x150] = INS_BMI;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BMI_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0x110] = INS_BMI;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BNE                                                                                              BNE      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BNE_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0x150] = INS_BNE;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BNE_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BNE;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BNE_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;

	// Initialize memory
	system.rom[0x1F0] = INS_BNE;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BNE_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BNE;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BNE_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;

	// Initialize memory
	system.rom[0x110] = INS_BNE;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BPL                                                                                              BPL      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BPL_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0x150] = INS_BPL;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BPL_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BPL;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BPL_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;

	// Initialize memory
	system.rom[0x1F0] = INS_BPL;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BPL_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BPL;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BPL_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;

	// Initialize memory
	system.rom[0x110] = INS_BPL;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BVC                                                                                              BVC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BVC_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0x150] = INS_BVC;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BVC_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BVC;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BVC_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;

	// Initialize memory
	system.rom[0x1F0] = INS_BVC;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BVC_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BVC;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BVC_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;

	// Initialize memory
	system.rom[0x110] = INS_BVC;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BVS                                                                                              BVS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BVS_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;

	// Initialize memory
	system.rom[0x150] = INS_BVS;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8152);
}

TEST(BVS_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0x150] = INS_BVS;
	system.rom[0x151] = 0x40;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8192);
}

TEST(BVS_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x81F0;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0x1F0] = INS_BVS;
	system.rom[0x1F1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8202);
}

TEST(BVS_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8150;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0x150] = INS_BVS;
	system.rom[0x151] = 0xC0;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8112);
}

TEST(BVS_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0x8110;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0x110] = INS_BVS;
	system.rom[0x111] = 0xE0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x80F2);
}