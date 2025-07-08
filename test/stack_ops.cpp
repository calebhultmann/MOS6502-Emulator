#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      TSX                                                                                              TSX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TSX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0;

	// Initialize memory
	system.rom[0] = INS_TSX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.X, 0);
}

TEST(TSX_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0x4F;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_TSX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(TSX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_TSX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.X, 0xFF);
}

TEST(TSX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.SP = 0x4F;

	// Initialize memory
	system.rom[0] = INS_TSX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      TXS                                                                                              TXS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TXS_TEST, CorrectlyModifiesStackPointer) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4F;

	// Initialize memory
	system.rom[0] = INS_TXS;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.SP, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PHA                                                                                              PHA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PHA_TEST, CorrectlyPushesToStack) {
	// 1 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_PHA;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.SP, 0xFE);
	EXPECT_EQ(system.ram[0x1FF], 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PHP                                                                                              PHP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PHP_TEST, CorrectlyPushesToStack) {
	// 1 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.P = 0b11011111;

	// Initialize memory
	system.rom[0] = INS_PHP;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0b11011111);
	EXPECT_EQ(system.cpu.SP, 0xFE);
	EXPECT_EQ(system.ram[0x1FF], 0b11011111);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PLA                                                                                              PLA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PLA_TEST, CorrectlyPullsFromStack) {
	// 1 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0xFE;

	// Initialize memory
	system.rom[0] = INS_PLA;
	system.ram[0x1FF] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0x4F);
}

TEST(PLA_TEST, SetsZeroFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0xFE;

	// Initialize memory
	system.rom[0] = INS_PLA;
	system.ram[0x1FF] = 0x0;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0x0);
}

TEST(PLA_TEST, ClearsZeroFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0xFE;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_PLA;
	system.ram[0x1FF] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0x4F);
}

TEST(PLA_TEST, SetsNegativeFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0xFE;

	// Initialize memory
	system.rom[0] = INS_PLA;
	system.ram[0x1FF] = 0x80;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0x80);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0x80);
}

TEST(PLA_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0xFE;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_PLA;
	system.ram[0x1FF] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0x4F);
}

TEST(PLA_TEST, WorksInTandemWithPHA) {
	// 2 Bytes, 7 Cycles
	
	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_PHA;
	system.rom[1] = INS_PLA;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);
	EXPECT_EQ(status, 0);

	system.cpu.A = 0;
	system.cpu.P |= system.cpu.Z;

	status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      PLP                                                                                              PLP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PLP_TEST, CorrectlyPullsFromStack) {
	// 1 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.SP = 0xFE;

	// Initialize memory
	system.rom[0] = INS_PLP;
	system.ram[0x1FF] = 0b11011111;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0b11011111);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0b11011111);
}

TEST(PLP_TEST, WorksInTandemWithPHP) {
	// 2 Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.P = 0b11011111;

	// Initialize memory
	system.rom[0] = INS_PHP;
	system.rom[1] = INS_PLP;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);
	EXPECT_EQ(status, 0);

	system.cpu.P = 0;

	status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0b11011111);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x1FF], 0b11011111);
}