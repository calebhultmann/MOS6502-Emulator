#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      JMP                                                                                              JMP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(JMP_TEST, Immediate) {
	// 3 Bytes, 3 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_JMP_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0xAF;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xAF10);
}

TEST(JMP_TEST, Indirect) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_JMP_IND;
	system.rom[1] = 0x10;
	system.rom[2] = 0xAF;
	system.rom[0x2F10] = 0x20;
	system.rom[0x2F11] = 0xBC;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xBC20);
}

TEST(JMP_TEST, IndirectJumpIncorrectlyFetchesAddressOnPageBoundary) {
	// 3 Bytes, 5 Cycles
	
	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_JMP_IND;
	system.rom[1] = 0xFF;
	system.rom[2] = 0x96;
	system.rom[0x16FF] = 0x20;
	system.rom[0x1600] = 0xBC;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xBC20);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      JSR                                                                                              JSR      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(JSR_TEST, CorrectlyFetchesSubroutineAddress) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_JSR_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0xAF;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xAF10);
}

TEST(JSR_TEST, CorrectlyPushesToStack) {
	// 3 Bytes, 6 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_JSR_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0xAF;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xAF10);
	EXPECT_EQ(system.cpu.SP, 0xFD);
	EXPECT_EQ(system.ram[0x01FE], 0x02);
	EXPECT_EQ(system.ram[0x01FF], 0x80);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      RTS                                                                                              RTS      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(RTS_TEST, CorrectlyFetchesReturnAddress) {
	// 1 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0xAF10;
	system.cpu.SP = 0xFD;

	// Initialize memory
	system.rom[0x2F10] = INS_RTS;
	system.ram[0x01FE] = 0x00;
	system.ram[0x01FF] = 0x80;


	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
}

TEST(RTS_TEST, CorrectlyPullsFromStack) {
	// 1 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0xAF10;
	system.cpu.SP = 0xFD;

	// Initialize memory
	system.rom[0x2F10] = INS_RTS;
	system.ram[0x01FE] = 0x00;
	system.ram[0x01FF] = 0x80;


	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.SP, 0xFF);
	EXPECT_EQ(system.ram[0x01FE], 0x00);
	EXPECT_EQ(system.ram[0x01FF], 0x80);
}