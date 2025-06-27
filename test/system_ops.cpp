#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      BRK                                                                                              BRK      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BRK_TEST, CorrectlyLoadsInterruptVector) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_BRK;
	cpu.mem[0xFFFE] = 0x00;
	cpu.mem[0xFFFF] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xC000);
}

TEST(BRK_TEST, SetsBreakFlag) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_BRK;
	cpu.mem[0xFFFE] = 0x00;
	cpu.mem[0xFFFF] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xC000);
	EXPECT_EQ(cpu.P | cpu.B, cpu.B);
}

TEST(BRK_TEST, DoesNotSetOtherFlags) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_BRK;
	cpu.mem[0xFFFE] = 0x00;
	cpu.mem[0xFFFF] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xC000);
	EXPECT_EQ(cpu.P, cpu.B);
}

TEST(BRK_TEST, DoesNotClearOtherFlags) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P = 0b11001111;

	// Initialize memory
	cpu.mem[0x200] = INS_BRK;
	cpu.mem[0xFFFE] = 0x00;
	cpu.mem[0xFFFF] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xC000);
	EXPECT_EQ(cpu.P, 0b11011111);
}

TEST(BRK_TEST, CorrectlyPushesInfoToStack) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P = 0b11001111;
	// Initialize memory
	cpu.mem[0x200] = INS_BRK;
	cpu.mem[0xFFFE] = 0x00;
	cpu.mem[0xFFFF] = 0xC0;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0xC000);
	EXPECT_EQ(cpu.P, 0b11011111);
	EXPECT_EQ(cpu.mem[0x1FF], 0x02);
	EXPECT_EQ(cpu.mem[0x1FE], 0x02);
	EXPECT_EQ(cpu.mem[0x1FD], 0b11011111);
}