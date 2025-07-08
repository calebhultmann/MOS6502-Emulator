#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      AND                                                                                              AND      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(AND_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x0094] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0x00C5] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF3;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x20;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF1;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x20;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF0;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_IM;
	system.rom[1] = 0b10101010;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(AND_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

TEST(AND_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b10101010;

	// Initialize memory
	system.rom[0] = INS_AND_IM;
	system.rom[1] = 0b11001100;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b10001000);
}

TEST(AND_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_AND_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010001);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      EOR                                                                                              EOR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(EOR_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x0094] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0x00C5] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF3;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x20;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF1;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x20;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF0;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_IM;
	system.rom[1] = 0b01010101;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(EOR_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

TEST(EOR_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_IM;
	system.rom[1] = 0b11001100;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b10011001);
}

TEST(EOR_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_EOR_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01100110);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      ORA                                                                                              ORA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ORA_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x0094] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0x00C5] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x84;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF3;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x20;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF1;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x20;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xF0;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_ORA_IM;
	system.rom[1] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(ORA_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

TEST(ORA_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_IM;
	system.rom[1] = 0b11001100;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b11011101);
}

TEST(ORA_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_ORA_IM;
	system.rom[1] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01110111);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      BIT                                                                                              BIT      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BIT_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, SetsZeroFlag) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b00001010;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, ClearsZeroFlag) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, SetsNegativeFlag) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b10000101;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, SetsOverflowFlag) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b01001010;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.V);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}

TEST(BIT_TEST, ClearsOverflowFlag) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.V;
	system.cpu.A = 0b01010101;

	// Initialize memory
	system.rom[0] = INS_BIT_ZP;
	system.rom[1] = 0xC4;
	system.ram[0xC4] = 0b00110011;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01010101);
}