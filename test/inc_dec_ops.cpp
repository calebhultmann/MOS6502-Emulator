#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      INC                                                                                              INC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(INC_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0x44);
}

TEST(INC_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xAF;

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0xBF] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xBF], 0x44);
}

TEST(INC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0x44);
}

TEST(INC_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0x44);
}

TEST(INC_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0x44);
}

TEST(INC_TEST, AbsoluteX_WithWrapAround) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x43;
	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xB003], 0x44);
}

TEST(INC_TEST, SetsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZP;
	cpu.mem[0x201] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.mem[0x10], 0);
}

TEST(INC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 1);
}

TEST(INC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x7F;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.mem[0x10], 0x80);
}

TEST(INC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_INC_ZP;
	cpu.mem[0x201] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.mem[0x10], 0);
}