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
	EXPECT_EQ(cpu.S, 0xFC);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      NOP                                                                                              NOP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(NOP_TEST, CorrectlyDoesNothing) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_NOP;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0b00000000);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      RTI                                                                                              RTI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(RTI_TEST, CorrectlyLoadsProgramCounter) {
	// 1 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0xC000;
	cpu.S = 0xFC;

	// Initialize memory
	cpu.mem[0xC000] = INS_RTI;

	cpu.mem[0x1FF] = 0x02;
	cpu.mem[0x1FE] = 0x02;
	cpu.mem[0x1FD] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
}

TEST(RTI_TEST, CorrectlyLoadsProcessorStatus) {
	// 1 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0xC000;
	cpu.S = 0xFC;

	// Initialize memory
	cpu.mem[0xC000] = INS_RTI;

	cpu.mem[0x1FF] = 0x02;
	cpu.mem[0x1FE] = 0x02;
	cpu.mem[0x1FD] = 0b11001111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0b11001111);

}

TEST(RTI_TEST, ClearsBreakFlag) {
	// 1 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0xC000;
	cpu.S = 0xFC;

	// Initialize memory
	cpu.mem[0xC000] = INS_RTI;

	cpu.mem[0x1FF] = 0x02;
	cpu.mem[0x1FE] = 0x02;
	cpu.mem[0x1FD] = 0b11011111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0b11001111);
}

TEST(RTI_TEST, CorrectlyPullsInfoFromStack) {
	// 1 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.PC = 0xC000;
	cpu.S = 0xFC;

	// Initialize memory
	cpu.mem[0xC000] = INS_RTI;

	cpu.mem[0x1FF] = 0x02;
	cpu.mem[0x1FE] = 0x02;
	cpu.mem[0x1FD] = 0b11011111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0b11001111);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
	EXPECT_EQ(cpu.mem[0x1FE], 0xFF);
	EXPECT_EQ(cpu.mem[0x1FD], 0xFF);
	EXPECT_EQ(cpu.S, 0xFF);
}