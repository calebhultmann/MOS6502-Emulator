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