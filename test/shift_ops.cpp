#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      ASL                                                                                              ASL      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ASL_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00101111;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01011110);
}

TEST(ASL_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_ASL_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0b01011110);
}

TEST(ASL_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ASL_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0b01011110);
}

TEST(ASL_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_ASL_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0b01011110);
}

TEST(ASL_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_ASL_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0b01011110);
}

TEST(ASL_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ASL_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0b01011110);
}

TEST(ASL_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(ASL_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000001;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000010);
}

TEST(ASL_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01000000;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b10000000);
}

TEST(ASL_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000001;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000010);
}

TEST(ASL_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b10000001;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
	EXPECT_EQ(system.cpu.A, 0b10);
}

TEST(ASL_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000001;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_ASL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000010);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      LSR                                                                                              LSR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(LSR_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00101110;

	// Initialize memory
	system.rom[0] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010111);
}

TEST(LSR_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LSR_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0b00010111);
}

TEST(LSR_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_LSR_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0b00010111);
}

TEST(LSR_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_LSR_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0b00010111);
}

TEST(LSR_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_LSR_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0b00010111);
}

TEST(LSR_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_LSR_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0b00010111);
}

TEST(LSR_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(LSR_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000010;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000001);
}

TEST(LSR_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000010;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000001);
}

TEST(LSR_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000011;

	// Initialize memory
	system.rom[0] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
	EXPECT_EQ(system.cpu.A, 0b00000001);
}

TEST(LSR_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000010;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_LSR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000001);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      ROL                                                                                              ROL      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ROL_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00101111;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01011110);
}

TEST(ROL_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_ROL_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0b01011110);
}

TEST(ROL_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ROL_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0b01011110);
}

TEST(ROL_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_ROL_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0b01011110);
}

TEST(ROL_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_ROL_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0b01011110);
}

TEST(ROL_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ROL_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00101111;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0b01011110);
}

TEST(ROL_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(ROL_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000001;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000010);
}

TEST(ROL_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b01000000;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b10000000);
}

TEST(ROL_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000001;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000010);
}

TEST(ROL_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b10000001;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
	EXPECT_EQ(system.cpu.A, 0b10);
}

TEST(ROL_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000001;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_ROL_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000011);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      ROR                                                                                              ROR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ROR_TEST, Accumulator) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00101110;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00010111);
}

TEST(ROR_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_ROR_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0b00010111);
}

TEST(ROR_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ROR_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x94], 0b00010111);
}

TEST(ROR_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_ROR_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0b00010111);
}

TEST(ROR_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_ROR_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0b00010111);
}

TEST(ROR_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ROR_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0b00101110;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0b00010111);
}

TEST(ROR_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(ROR_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000010;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b00000001);
}

TEST(ROR_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000000;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b10000000);
}

TEST(ROR_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b10000000;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0b01000000);
}

TEST(ROR_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b10000001;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
	EXPECT_EQ(system.cpu.A, 0b01000000);
}

TEST(ROR_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0b00000000;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_ROR_ACC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0b10000000);
}