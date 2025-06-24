#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      AND                                                                                              AND      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(AND_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x0094] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0x00C5] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF3;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x20;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x5B] = 0x10;
	cpu.mem[0x5C] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF1;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x2C] = 0x10;
	cpu.mem[0x2D] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x20;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xAF30] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF0;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xB000] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_IM;
	cpu.mem[0x201] = 0b10101010;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(AND_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

TEST(AND_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b10101010;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_IM;
	cpu.mem[0x201] = 0b11001100;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b10001000);
}

TEST(AND_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_AND_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010001);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      EOR                                                                                              EOR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(EOR_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x0094] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0x00C5] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF3;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x20;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x5B] = 0x10;
	cpu.mem[0x5C] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF1;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x2C] = 0x10;
	cpu.mem[0x2D] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x20;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xAF30] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF0;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xB000] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_IM;
	cpu.mem[0x201] = 0b01010101;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(EOR_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

TEST(EOR_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_IM;
	cpu.mem[0x201] = 0b11001100;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b10011001);
}

TEST(EOR_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_EOR_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01100110);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      ORA                                                                                              ORA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ORA_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x0094] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0x00C5] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x84;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF3;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_ABSY;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x20;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x5B] = 0x10;
	cpu.mem[0x5C] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF1;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_INDX;
	cpu.mem[0x201] = 0x3B;
	cpu.mem[0x2C] = 0x10;
	cpu.mem[0x2D] = 0xAF;
	cpu.mem[0xAF10] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x20;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xAF30] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xF0;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_INDY;
	cpu.mem[0x201] = 0x30;
	cpu.mem[0x30] = 0x10;
	cpu.mem[0x31] = 0xAF;
	cpu.mem[0xB000] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_IM;
	cpu.mem[0x201] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(ORA_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}

TEST(ORA_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_IM;
	cpu.mem[0x201] = 0b11001100;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b11011101);
}

TEST(ORA_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;
	cpu.A = 0b01010101;

	// Initialize memory
	cpu.mem[0x200] = INS_ORA_IM;
	cpu.mem[0x201] = 0b00110011;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01110111);
}