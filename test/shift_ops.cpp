#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      ASL                                                                                              ASL      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ASL_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00101111;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01011110);
}

TEST(ASL_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0b01011110);
}

TEST(ASL_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x94] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x94], 0b01011110);
}

TEST(ASL_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0b01011110);
}

TEST(ASL_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0b01011110);
}

TEST(ASL_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0b01011110);
}

TEST(ASL_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(ASL_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000001;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000010);
}

TEST(ASL_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01000000;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b10000000);
}

TEST(ASL_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000001;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000010);
}

TEST(ASL_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b10000001;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.C);
	EXPECT_EQ(cpu.A, 0b10);
}

TEST(ASL_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000001;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000010);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      LSR                                                                                              LSR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LSR_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00101110;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010111);
}

TEST(LSR_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0b00010111);
}

TEST(LSR_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x94] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x94], 0b00010111);
}

TEST(LSR_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0b00010111);
}

TEST(LSR_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0b00010111);
}

TEST(LSR_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0b00010111);
}

TEST(LSR_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(LSR_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000010;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000001);
}

TEST(LSR_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000010;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000001);
}

TEST(LSR_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000011;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.C);
	EXPECT_EQ(cpu.A, 0b00000001);
}

TEST(LSR_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000010;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000001);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      ROL                                                                                              ROL      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ROL_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00101111;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01011110);
}

TEST(ROL_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0b01011110);
}

TEST(ROL_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x94] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x94], 0b01011110);
}

TEST(ROL_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0b01011110);
}

TEST(ROL_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0b01011110);
}

TEST(ROL_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00101111;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0b01011110);
}

TEST(ROL_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(ROL_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000001;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000010);
}

TEST(ROL_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b01000000;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b10000000);
}

TEST(ROL_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000001;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000010);
}

TEST(ROL_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b10000001;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.C);
	EXPECT_EQ(cpu.A, 0b10);
}

TEST(ROL_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000001;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000011);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      ROR                                                                                              ROR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ROR_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00101110;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00010111);
}

TEST(ROR_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ZP;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x10] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x10], 0b00010111);
}

TEST(ROR_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ZPX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x94] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0x94], 0b00010111);
}

TEST(ROR_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0xF5;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ZPX;
	cpu.mem[0x201] = 0xD0;
	cpu.mem[0xC5] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x202);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xC5], 0b00010111);
}

TEST(ROR_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ABS;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF10], 0b00010111);
}

TEST(ROR_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x84;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ABSX;
	cpu.mem[0x201] = 0x10;
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF94] = 0b00101110;

	// Run the expected number of cycles
	int status = cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x203);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.mem[0xAF94], 0b00010111);
}

TEST(ROR_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.Z);
	EXPECT_EQ(cpu.A, 0);
}

TEST(ROR_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000010;
	cpu.P |= cpu.Z;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b00000001);
}

TEST(ROR_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000000;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b10000000);
}

TEST(ROR_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b10000000;
	cpu.P |= cpu.N;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(ROR_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b10000001;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.C);
	EXPECT_EQ(cpu.A, 0b01000000);
}

TEST(ROR_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.A = 0b00000000;
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.N);
	EXPECT_EQ(cpu.A, 0b10000000);
}