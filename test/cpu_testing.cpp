#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      LDA                                                                                              LDA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LDA_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x0094] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0x00C5] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x20;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x5B] = 0x10;
	cpu.mem[0x5C] = 0xAF;
	cpu.mem[0xAF10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF1;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x2C] = 0x10;
	cpu.mem[0x2D] = 0xAF;
	cpu.mem[0xAF10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x20;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xAF30] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF0;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xB000] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(LDA_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

TEST(LDA_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0xFF;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0xFF);
}

TEST(LDA_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      LDX                                                                                              LDX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LDX_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, ZeroPageY) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_ZPY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x0094] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, ZeroPageY_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_ZPY;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0x00C5] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_IM;
	cpu.mem[0x201] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.X, 0);
}

TEST(LDX_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

TEST(LDX_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_IM;
	cpu.mem[0x201] = 0xFF;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.X, 0xFF);
}

TEST(LDX_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_LDX_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      LDY                                                                                              LDY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LDY_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x0094] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0x00C5] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_IM;
	cpu.mem[0x201] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.Y, 0);
}

TEST(LDY_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

TEST(LDY_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_IM;
	cpu.mem[0x201] = 0xFF;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.Y, 0xFF);
}

TEST(LDY_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_LDY_IM;
	cpu.mem[0x201] = 0x4F;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      STA                                                                                              STA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(STA_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles
	
	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ZP;
	cpu.mem[0x201] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0x4F);
}

TEST(STA_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ZPX;
	cpu.mem[0x201] = 0x10;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x94], 0x4F);
}

TEST(STA_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ZPX;
	cpu.mem[0x201] = 0xD0;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0x4F);
}

TEST(STA_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0x4F);
}

TEST(STA_TEST, AbsoluteX) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0x4F);
}

TEST(STA_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xB003], 0x4F);
}

TEST(STA_TEST, AbsoluteY) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0x4F);
}

TEST(STA_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xB003], 0x4F);
}

TEST(STA_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0x20;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x5B] = 0x10;
	cpu.mem[0x5C] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0x4F);
}

TEST(STA_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.X = 0xF1;

	// Initialize memory
	cpu.mem[0x200] = INS_STA_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x2C] = 0x10;
	cpu.mem[0x2D] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0x4F);
}

TEST(STA_TEST, IndirectY) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0x20;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF30], 0x4F);
}

TEST(STA_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0x4F;
	cpu.Y = 0xF0;

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xB000], 0x4F);
}