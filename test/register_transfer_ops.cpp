#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      TAX                                                                                              TAX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TAX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_TAX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.X, 0);
}

TEST(TAX_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_TAX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(TAX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0xFF;

	// Initialize memory
	cpu.mem[0x200] = INS_TAX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.X, 0xFF);
}

TEST(TAX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_TAX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      TAY                                                                                              TAY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TAY_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_TAY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.Y, 0);
}

TEST(TAY_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_TAY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(TAY_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0xFF;

	// Initialize memory
	cpu.mem[0x200] = INS_TAY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.Y, 0xFF);
}

TEST(TAY_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_TAY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}