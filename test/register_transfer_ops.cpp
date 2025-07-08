#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      TAX                                                                                              TAX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TAX_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_TAX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.X, 0);
}

TEST(TAX_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_TAX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

TEST(TAX_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0xFF;

	// Initialize memory
	system.rom[0] = INS_TAX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.X, 0xFF);
}

TEST(TAX_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_TAX;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.X, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      TAY                                                                                              TAY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TAY_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0;

	// Initialize memory
	system.rom[0] = INS_TAY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.Y, 0);
}

TEST(TAY_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_TAY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

TEST(TAY_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0xFF;

	// Initialize memory
	system.rom[0] = INS_TAY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.Y, 0xFF);
}

TEST(TAY_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_TAY;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.Y, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      TXA                                                                                              TXA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TXA_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0;

	// Initialize memory
	system.rom[0] = INS_TXA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(TXA_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4F;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_TXA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(TXA_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0xFF;

	// Initialize memory
	system.rom[0] = INS_TXA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0xFF);
}

TEST(TXA_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.X = 0x4F;

	// Initialize memory
	system.rom[0] = INS_TXA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      TYA                                                                                              TYA      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(TYA_TEST, SetsZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0;

	// Initialize memory
	system.rom[0] = INS_TYA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(TYA_TEST, ClearZeroFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4F;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_TYA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}

TEST(TYA_TEST, SetsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0xFF;

	// Initialize memory
	system.rom[0] = INS_TYA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0xFF);
}

TEST(TYA_TEST, ClearsNegativeFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.N;
	system.cpu.Y = 0x4F;

	// Initialize memory
	system.rom[0] = INS_TYA;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x4F);
}