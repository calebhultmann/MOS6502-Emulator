#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      ADC                                                                                              ADC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ADC_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x94] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0x20;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x5B] = 0x10;
	cpu.mem[0x5C] = 0xAF;
	cpu.mem[0xAF10] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0xF1;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x2C] = 0x10;
	cpu.mem[0x2D] = 0xAF;
	cpu.mem[0xAF10] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0x20;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xAF30] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0xF0;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xB000] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}



TEST(ADC_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x0;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(ADC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x8F;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 1;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0x90);
}

TEST(ADC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}

TEST(ADC_TEST, SetsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0xF0;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x2B;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.C);
	EXPECT_EQ(cpu.A, 0x1B);
}

TEST(ADC_TEST, ClearsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7C);
}

TEST(ADC_TEST, SetsOverflowFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x84;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.C | cpu.V);
	EXPECT_EQ(cpu.A, 0x08);
}

TEST(ADC_TEST, ClearsOverflowFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x200] = INS_ADC_IM;
	cpu.mem[0x201] = 0x2C;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x7B);
}