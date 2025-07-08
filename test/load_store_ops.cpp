#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include <iostream>

/*----------------------------------------------------------------------------------------------------------------*/
/*      LDA                                                                                              LDA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LDA_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDA_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDA_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDA_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_LDA_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDA_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDA_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_LDA_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDA_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF3;

	// Initialize memory
	system.rom[0] = INS_LDA_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x20;

	// Initialize memory
	system.rom[0] = INS_LDA_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF1;

	// Initialize memory
	system.rom[0] = INS_LDA_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x20;

	// Initialize memory
	system.rom[0] = INS_LDA_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF0;

	// Initialize memory
	system.rom[0] = INS_LDA_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDA_IM;
	system.rom[1] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(LDA_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_LDA_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(LDA_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDA_IM;
	system.rom[1] = 0xFF;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0xFF);
}

TEST(LDA_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_LDA_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      LDX                                                                                              LDX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LDX_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDX_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDX_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, ZeroPageY) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDX_ZPY;
	system.rom[1] = 0x10;
	system.ram[0x0094] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, ZeroPageY_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF5;

	// Initialize memory
	system.rom[0] = INS_LDX_ZPY;
	system.rom[1] = 0xD0;
	system.ram[0x00C5] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDX_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDX_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF3;

	// Initialize memory
	system.rom[0] = INS_LDX_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDX_IM;
	system.rom[1] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.X, 0);
}

TEST(LDX_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_LDX_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(LDX_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDX_IM;
	system.rom[1] = 0xFF;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.X, 0xFF);
}

TEST(LDX_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_LDX_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      LDY                                                                                              LDY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LDY_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDY_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDY_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDY_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x0094] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_LDY_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0x00C5] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDY_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_LDY_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_LDY_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDY_IM;
	system.rom[1] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.Y, 0);
}

TEST(LDY_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_LDY_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(LDY_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LDY_IM;
	system.rom[1] = 0xFF;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.Y, 0xFF);
}

TEST(LDY_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_LDY_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      STA                                                                                              STA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(STA_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles
	
	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_STA_ZP;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0x4F);
}

TEST(STA_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_STA_ZPX;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0x4F);
}

TEST(STA_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_STA_ZPX;
	system.rom[1] = 0xD0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0x4F);
}

TEST(STA_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_STA_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x4F);
}

TEST(STA_TEST, AbsoluteX) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_STA_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0x4F);
}

TEST(STA_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_STA_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7F03], 0x4F);
}

TEST(STA_TEST, AbsoluteY) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_STA_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0x4F);
}

TEST(STA_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0xF3;

	// Initialize memory
	system.rom[0] = INS_STA_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7F03], 0x4F);
}

TEST(STA_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x20;

	// Initialize memory
	system.rom[0] = INS_STA_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x4F);
}

TEST(STA_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF1;

	// Initialize memory
	system.rom[0] = INS_STA_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x4F);
}

TEST(STA_TEST, IndirectY) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0x20;

	// Initialize memory
	system.rom[0] = INS_STA_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E30], 0x4F);
}

TEST(STA_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0xF0;

	// Initialize memory
	system.rom[0] = INS_STA_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7F00], 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      STX                                                                                              STX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(STX_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4F;

	// Initialize memory
	system.rom[0] = INS_STX_ZP;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0x4F);
}

TEST(STX_TEST, ZeroPageY) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4F;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_STX_ZPY;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0x4F);
}

TEST(STX_TEST, ZeroPageY_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	
	system.cpu.X = 0x4F;
	system.cpu.Y = 0xF5;
	// Initialize memory
	system.rom[0] = INS_STX_ZPY;
	system.rom[1] = 0xD0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0x4F);
}

TEST(STX_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4F;

	// Initialize memory
	system.rom[0] = INS_STX_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      STY                                                                                              STY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(STY_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4F;

	// Initialize memory
	system.rom[0] = INS_STY_ZP;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0x4F);
}

TEST(STY_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4F;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_STY_ZPX;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0x4F);
}

TEST(STY_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4F;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_STY_ZPX;
	system.rom[1] = 0xD0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0x4F);
}

TEST(STY_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4F;

	// Initialize memory
	system.rom[0] = INS_STY_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x4F);
}