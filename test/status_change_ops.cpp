#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLC                                                                                              CLC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLC_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_CLC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLD                                                                                              CLD      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLD_TEST, ClearsDecimalFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.D;

	// Initialize memory
	system.rom[0] = INS_CLD;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLI                                                                                              CLI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLI_TEST, ClearsInterruptFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.I;

	// Initialize memory
	system.rom[0] = INS_CLI;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLV                                                                                              CLV      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLC_TEST, ClearsOverflowFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0] = INS_CLV;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SEC                                                                                              SEC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SEC_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_SEC;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SED                                                                                              SED      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SED_TEST, SetsDecimalFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_SED;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.D);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SEI                                                                                              SEI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SEI_TEST, SetsInterruptFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_SEI;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, system.cpu.I);
}