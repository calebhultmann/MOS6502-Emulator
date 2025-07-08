#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      INC                                                                                              INC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(INC_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_INC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0x44);
}

TEST(INC_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x7E;

	// Initialize memory
	system.rom[0] = INS_INC_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x8E] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x8E], 0x44);
}

TEST(INC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_INC_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0x44);
}

TEST(INC_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_INC_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x44);
}

TEST(INC_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_INC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0x44);
}

TEST(INC_TEST, AbsoluteX_WithWrapAround) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_INC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x43;
	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7F03], 0x44);
}

TEST(INC_TEST, SetsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_INC_ZP;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.ram[0x10], 0);
}

TEST(INC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_INC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 1);
}

TEST(INC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_INC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x7F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.ram[0x10], 0x80);
}

TEST(INC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_INC_ZP;
	system.rom[1] = 0x10;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.ram[0x10], 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      INX                                                                                              INX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(INX_TEST, CorrectlyIncrementsXRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x43;

	// Initialize memory
	system.rom[0] = INS_INX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x44);
}

TEST(INX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xFF;

	// Initialize memory
	system.rom[0] = INS_INX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.X, 0);
}

TEST(INX_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_INX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 1);
}

TEST(INX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x7F;

	// Initialize memory
	system.rom[0] = INS_INX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.X, 0x80);
}

TEST(INX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xFF;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_INX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.X, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      INY                                                                                              INY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(INY_TEST, CorrectlyIncrementsYRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x43;

	// Initialize memory
	system.rom[0] = INS_INY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x44);
}

TEST(INY_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xFF;

	// Initialize memory
	system.rom[0] = INS_INY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.Y, 0);
}

TEST(INY_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_INY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 1);
}

TEST(INY_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x7F;

	// Initialize memory
	system.rom[0] = INS_INY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.Y, 0x80);
}

TEST(INY_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xFF;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_INY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.Y, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      DEC                                                                                              DEC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(DEC_TEST, ZeroPage) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_DEC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0x42);
}

TEST(DEC_TEST, ZeroPageX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x7E;

	// Initialize memory
	system.rom[0] = INS_DEC_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x8E] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x8E], 0x42);
}

TEST(DEC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_DEC_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0xC5], 0x42);
}

TEST(DEC_TEST, Absolute) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_DEC_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E10], 0x42);
}

TEST(DEC_TEST, AbsoluteX) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_DEC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x43;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7E94], 0x42);
}

TEST(DEC_TEST, AbsoluteX_WithWrapAround) {
	// 3 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_DEC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x43;
	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x7F03], 0x42);
}

TEST(DEC_TEST, SetsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_DEC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 1;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.ram[0x10], 0);
}

TEST(DEC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_DEC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.ram[0x10], 0xFF);
}

TEST(DEC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_DEC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.ram[0x10], 0xFF);
}

TEST(DEC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_DEC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x80;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.ram[0x10], 0x7F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      DEX                                                                                              DEX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(DEX_TEST, CorrectlyDecrementsXRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x43;

	// Initialize memory
	system.rom[0] = INS_DEX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x42);
}

TEST(DEX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x1;

	// Initialize memory
	system.rom[0] = INS_DEX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.X, 0);
}

TEST(DEX_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_DEX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.X, 0xFF);
}

TEST(DEX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0;

	// Initialize memory
	system.rom[0] = INS_DEX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.X, 0xFF);
}

TEST(DEX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x80;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_DEX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x7F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      DEY                                                                                              DEY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(DEY_TEST, CorrectlyDecrementsYRegister) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x43;

	// Initialize memory
	system.rom[0] = INS_DEY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x42);
}

TEST(DEY_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x1;

	// Initialize memory
	system.rom[0] = INS_DEY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.Y, 0);
}

TEST(DEY_TEST, ClearsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_DEY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.Y, 0xFF);
}

TEST(DEY_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0;

	// Initialize memory
	system.rom[0] = INS_DEY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.Y, 0xFF);
}

TEST(DEY_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x80;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_DEY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x7F);
}