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

/*----------------------------------------------------------------------------------------------------------------*/
/*      JSR                                                                                              JSR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(JSR_TEST, CorrectlyFetchesSubroutineAddress) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_JSR_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xAF10);
}

TEST(JSR_TEST, CorrectlyPushesToStack) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_JSR_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xAF10);
	EXPECT_EQ(cpu.S, 0xFD);
	EXPECT_EQ(cpu.mem[0x01FE], 0x02);
	EXPECT_EQ(cpu.mem[0x01FF], 0x02);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      RTS                                                                                              RTS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(RTS_TEST, CorrectlyFetchesReturnAddress) {
	// 1 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0xAF10;
	cpu.S = 0xFD;

	// Initialize memory
	cpu.mem[0xAF10] = INS_RTS;
	cpu.mem[0x01FE] = 0x00;
	cpu.mem[0x01FF] = 0x02;


	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
}

TEST(RTS_TEST, CorrectlyPullsFromStack) {
	// 1 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0xAF10;
	cpu.S = 0xFD;

	// Initialize memory
	cpu.mem[0xAF10] = INS_RTS;
	cpu.mem[0x01FE] = 0x00;
	cpu.mem[0x01FF] = 0x02;


	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x01FE], 0xFF);
	EXPECT_EQ(cpu.mem[0x01FF], 0xFF);
}