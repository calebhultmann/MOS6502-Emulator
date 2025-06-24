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

/*----------------------------------------------------------------------------------------------------------------*/
/*      PHA                                                                                              PHA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PHA_TEST, CorrectlyPushesToStack) {
	// 1 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_PHA;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.S, 0xFE);
	EXPECT_EQ(cpu.mem[0x1FF], 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PHP                                                                                              PHP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PHP_TEST, CorrectlyPushesToStack) {
	// 1 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P = 0b11011111;

	// Initialize memory
	cpu.mem[0x200] = INS_PHP;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0b11011111);
	EXPECT_EQ(cpu.S, 0xFE);
	EXPECT_EQ(cpu.mem[0x1FF], 0b11011111);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PLA                                                                                              PLA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PLA_TEST, CorrectlyPullsFromStack) {
	// 1 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0xFE;

	// Initialize memory
	cpu.mem[0x200] = INS_PLA;
	cpu.mem[0x1FF] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

TEST(PLA_TEST, SetsZeroFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0xFE;

	// Initialize memory
	cpu.mem[0x200] = INS_PLA;
	cpu.mem[0x1FF] = 0x0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

TEST(PLA_TEST, ClearsZeroFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0xFE;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_PLA;
	cpu.mem[0x1FF] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

TEST(PLA_TEST, SetsNegativeFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0xFE;

	// Initialize memory
	cpu.mem[0x200] = INS_PLA;
	cpu.mem[0x1FF] = 0x80;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0x80);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

TEST(PLA_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0xFE;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_PLA;
	cpu.mem[0x1FF] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

TEST(PLA_TEST, WorksInTandemWithPHA) {
	// 2 Bytes, 7 Cycles
	
	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_PHA;
	cpu.mem[0x201] = INS_PLA;

	// Run the expected number of cycles
	int status = cpu.Run(3);
	EXPECT_EQ(status, 0);

	cpu.A = 0;
	cpu.P |= cpu.Z;

	status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PLP                                                                                              PLP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PLP_TEST, CorrectlyPullsFromStack) {
	// 1 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.S = 0xFE;

	// Initialize memory
	cpu.mem[0x200] = INS_PLP;
	cpu.mem[0x1FF] = 0b11011111;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0b11011111);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}

TEST(PLP_TEST, WorksInTandemWithPHP) {
	// 2 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P = 0b11011111;

	// Initialize memory
	cpu.mem[0x200] = INS_PHP;
	cpu.mem[0x201] = INS_PLP;

	// Run the expected number of cycles
	int status = cpu.Run(3);
	EXPECT_EQ(status, 0);

	cpu.P = 0;

	status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0b11011111);
	EXPECT_EQ(cpu.S, 0xFF);
	EXPECT_EQ(cpu.mem[0x1FF], 0xFF);
}