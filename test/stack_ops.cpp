#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      TSX                                                                                              TSX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TSX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_TSX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.X, 0);
}

TEST(TSX_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0x4F;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_TSX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(TSX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_TSX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.X, 0xFF);
}

TEST(TSX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;
	cpu.S = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_TSX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      TXS                                                                                              TXS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TXS_TEST, CorrectlyModifiesStackPointer) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_TXS;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.S, 0x4F);
}

///*----------------------------------------------------------------------------------------------------------------*/
///*      TSX                                                                                              TSX      */
///*----------------------------------------------------------------------------------------------------------------*/
//TEST(TSX_TEST, CorrectlyPullsFromStack) {
//	// 1 Bytes, 2 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.S = 0xFE;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TSX;
//	cpu.mem[0x1FF] = 0x4F;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x201);
//	EXPECT_EQ(cpu.P, 0);
//	EXPECT_EQ(cpu.S, 0xFF);
//	EXPECT_EQ(cpu.X, 0x4F);
//	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
//}
//
//TEST(TSX_TEST, SetsZeroFlag) {
//	// 1 Bytes, 2 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.S = 0xFE;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TSX;
//	cpu.mem[0x1FF] = 0x00;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x201);
//	EXPECT_EQ(cpu.P, cpu.Z);
//	EXPECT_EQ(cpu.S, 0xFF);
//	EXPECT_EQ(cpu.X, 0x4F);
//	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
//}
//
//TEST(TSX_TEST, ClearsZeroFlag) {
//	// 1 Bytes, 2 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.P |= cpu.Z;
//	cpu.S = 0xFE;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TSX;
//	cpu.mem[0x1FF] = 0x4F;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x201);
//	EXPECT_EQ(cpu.P, 0);
//	EXPECT_EQ(cpu.S, 0xFF);
//	EXPECT_EQ(cpu.X, 0x4F);
//	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
//}
//
//TEST(TSX_TEST, SetsNegativeFlag) {
//	// 1 Bytes, 2 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.S = 0xFE;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TSX;
//	cpu.mem[0x1FF] = 0x80;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x201);
//	EXPECT_EQ(cpu.P, cpu.N);
//	EXPECT_EQ(cpu.S, 0xFF);
//	EXPECT_EQ(cpu.X, 0x80);
//	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
//}
//
//TEST(TSX_TEST, ClearsNegativeFlag) {
//	// 1 Bytes, 2 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.P |= cpu.N;
//	cpu.S = 0xFE;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TSX;
//	cpu.mem[0x1FF] = 0x4F;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x201);
//	EXPECT_EQ(cpu.P, 0);
//	EXPECT_EQ(cpu.S, 0xFF);
//	EXPECT_EQ(cpu.X, 0x4F);
//	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
//}
//
///*----------------------------------------------------------------------------------------------------------------*/
///*      TXS                                                                                              TXS      */
///*----------------------------------------------------------------------------------------------------------------*/
//TEST(TXS_TEST, CorrectlyPushesToStack) {
//	// 1 Bytes, 2 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.X = 0x4F;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TXS;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x201);
//	EXPECT_EQ(cpu.P, 0);
//	EXPECT_EQ(cpu.S, 0xFE);
//	EXPECT_EQ(cpu.X, 0x4F);
//	EXPECT_EQ(cpu.mem[0x1FF], 0x4F);
//}
//
//TEST(TXS_TEST, WorksInTandemWithTSX) {
//	// 4 Bytes, 6 Cycles
//
//	// Initialize CPU
//	CPU cpu;
//	cpu.Reset();
//	cpu.X = 0x4F;
//
//	// Initialize memory
//	cpu.mem[0x200] = INS_TXS;
//	cpu.mem[0x201] = INS_LDX_IM;
//	cpu.mem[0x202] = 0x00;
//	cpu.mem[0x203] = INS_TSX;
//
//	// Run the expected number of cycles
//	int status = cpu.Run(2);
//
//	// Check test correctness
//	EXPECT_EQ(status, 0);
//	EXPECT_EQ(cpu.PC, 0x202);
//	EXPECT_EQ(cpu.P, 0);
//	EXPECT_EQ(cpu.S, 0xFE);
//	EXPECT_EQ(cpu.X, 0x4F);
//	EXPECT_EQ(cpu.mem[0x1FF], 0x4F);
//}