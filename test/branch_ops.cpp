#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      BCC                                                                                              BCC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BCC_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x350] = INS_BCC;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BCC_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BCC;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BCC_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BCC;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BCC_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BCC;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BCC_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;

	// Initialize memory
	cpu.mem[0x310] = INS_BCC;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BCS                                                                                              BCS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BCS_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BCS;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BCS_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x350] = INS_BCS;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BCS_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BCS;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BCS_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x350] = INS_BCS;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BCS_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x310] = INS_BCS;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BEQ                                                                                              BEQ      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BEQ_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BEQ;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BEQ_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x350] = INS_BEQ;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BEQ_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BEQ;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BEQ_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x350] = INS_BEQ;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BEQ_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x310] = INS_BEQ;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BMI                                                                                              BMI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BMI_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BMI;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BMI_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x350] = INS_BMI;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BMI_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BMI;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BMI_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x350] = INS_BMI;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BMI_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x310] = INS_BMI;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BNE                                                                                              BNE      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BNE_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x350] = INS_BNE;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BNE_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BNE;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BNE_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BNE;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BNE_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BNE;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BNE_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;

	// Initialize memory
	cpu.mem[0x310] = INS_BNE;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BPL                                                                                              BPL      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BPL_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x350] = INS_BPL;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BPL_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BPL;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BPL_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BPL;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BPL_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BPL;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BPL_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;

	// Initialize memory
	cpu.mem[0x310] = INS_BPL;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BVC                                                                                              BVC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BVC_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x350] = INS_BVC;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BVC_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BVC;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BVC_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BVC;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BVC_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BVC;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BVC_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;

	// Initialize memory
	cpu.mem[0x310] = INS_BVC;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BVS                                                                                              BVS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BVS_TEST, BranchFails) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;

	// Initialize memory
	cpu.mem[0x350] = INS_BVS;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x352);
}

TEST(BVS_TEST, BranchSucceeds_PositiveJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x350] = INS_BVS;
	cpu.mem[0x351] = 0x40;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x392);
}

TEST(BVS_TEST, BranchSucceeds_PositiveJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x3F0;
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x3F0] = INS_BVS;
	cpu.mem[0x3F1] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x402);
}

TEST(BVS_TEST, BranchSucceeds_NegativeJump) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x350;
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x350] = INS_BVS;
	cpu.mem[0x351] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x312);
}

TEST(BVS_TEST, BranchSucceeds_NegativeJump_WithPageCross) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0x310;
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x310] = INS_BVS;
	cpu.mem[0x311] = 0xE0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x2F2);
}