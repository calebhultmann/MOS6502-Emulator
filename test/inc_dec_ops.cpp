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

/*----------------------------------------------------------------------------------------------------------------*/
/*      INX                                                                                              INX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(INX_TEST, CorrectlyIncrementsXRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x43;

	// Initialize memory
	cpu.mem[0x200] = INS_INX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x44);
}

TEST(INX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xFF;

	// Initialize memory
	cpu.mem[0x200] = INS_INX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.X, 0);
}

TEST(INX_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_INX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 1);
}

TEST(INX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x7F;

	// Initialize memory
	cpu.mem[0x200] = INS_INX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.X, 0x80);
}

TEST(INX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xFF;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_INX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.X, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      INY                                                                                              INY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(INY_TEST, CorrectlyIncrementsYRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x43;

	// Initialize memory
	cpu.mem[0x200] = INS_INY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x44);
}

TEST(INY_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xFF;

	// Initialize memory
	cpu.mem[0x200] = INS_INY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.Y, 0);
}

TEST(INY_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_INY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 1);
}

TEST(INY_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x7F;

	// Initialize memory
	cpu.mem[0x200] = INS_INY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.Y, 0x80);
}

TEST(INY_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0xFF;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_INY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.Y, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      DEC                                                                                              DEC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(DEC_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0x42);
}

TEST(DEC_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xAF;

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0xBF] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xBF], 0x42);
}

TEST(DEC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0x42);
}

TEST(DEC_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0x42);
}

TEST(DEC_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0x43;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0x42);
}

TEST(DEC_TEST, AbsoluteX_WithWrapAround) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF3;

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xB003] = 0x43;
	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xB003], 0x42);
}

TEST(DEC_TEST, SetsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 1;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.mem[0x10], 0);
}

TEST(DEC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.mem[0x10], 0xFF);
}

TEST(DEC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.mem[0x10], 0xFF);
}

TEST(DEC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_DEC_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0x80;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0x7F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      DEX                                                                                              DEX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(DEX_TEST, CorrectlyDecrementsXRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x43;

	// Initialize memory
	cpu.mem[0x200] = INS_DEX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x42);
}

TEST(DEX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x1;

	// Initialize memory
	cpu.mem[0x200] = INS_DEX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.X, 0);
}

TEST(DEX_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_DEX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.X, 0xFF);
}

TEST(DEX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_DEX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.X, 0xFF);
}

TEST(DEX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x80;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_DEX;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.X, 0x7F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      DEY                                                                                              DEY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(DEY_TEST, CorrectlyDecrementsYRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x43;

	// Initialize memory
	cpu.mem[0x200] = INS_DEY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x42);
}

TEST(DEY_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x1;

	// Initialize memory
	cpu.mem[0x200] = INS_DEY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.Y, 0);
}

TEST(DEY_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_DEY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.Y, 0xFF);
}

TEST(DEY_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_DEY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.Y, 0xFF);
}

TEST(DEY_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.Y = 0x80;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_DEY;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.Y, 0x7F);
}