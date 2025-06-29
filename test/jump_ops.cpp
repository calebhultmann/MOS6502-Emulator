#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      JMP                                                                                              JMP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(JMP_TEST, Immediate) {
	// 3 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_JMP_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xAF10);
}

TEST(JMP_TEST, Indirect) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_JMP_IND;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x20;
	cpu.mem[0xAF11] = 0xBC;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xBC20);
}

TEST(JMP_TEST, IndirectJumpIncorrectlyFetchesAddressOnPageBoundary) {
	// 3 Bytes, 5 Cycles
	
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_JMP_IND;
	cpu.mem[0x201] = 0xFF;
	cpu.mem[0x202] = 0x16;
	cpu.mem[0x16FF] = 0x20;
	cpu.mem[0x1600] = 0xBC;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xBC20);
}

