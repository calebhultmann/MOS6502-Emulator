#include <gtest/gtest.h>
#include "bus.h"
#include "MOS6502.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      BRK                                                                                              BRK      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(BRK_TEST, CorrectlyLoadsInterruptVector) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_BRK;
	system.vectors[4] = 0x00;
	system.vectors[5] = 0xA0;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xA000);
}

TEST(BRK_TEST, SetsBreakFlag) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_BRK;
	system.vectors[4] = 0x00;
	system.vectors[5] = 0xA0;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xA000);
	EXPECT_EQ(system.cpu.P | system.cpu.B, system.cpu.B);
}

TEST(BRK_TEST, DoesNotSetOtherFlags) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_BRK;
	system.vectors[4] = 0x00;
	system.vectors[5] = 0xA0;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xA000);
	EXPECT_EQ(system.cpu.P, system.cpu.B);
}

TEST(BRK_TEST, DoesNotClearOtherFlags) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.P = 0b11001111;

	// Initialize memory
	system.rom[0] = INS_BRK;
	system.vectors[4] = 0x00;
	system.vectors[5] = 0xA0;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xA000);
	EXPECT_EQ(system.cpu.P, 0b11011111);
}

TEST(BRK_TEST, CorrectlyPushesInfoToStack) {
	// 2 (1) Bytes, 7 Cycles

	// Initialize system
	Bus system;
	system.cpu.P = 0b11001111;
	// Initialize memory
	system.rom[0] = INS_BRK;
	system.vectors[4] = 0x00;
	system.vectors[5] = 0xA0;

	// Run the expected number of cycles
	int status = system.cpu.Run(7);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0xA000);
	EXPECT_EQ(system.cpu.P, 0b11011111);
	EXPECT_EQ(system.ram[0x1FF], 0x80);
	EXPECT_EQ(system.ram[0x1FE], 0x02);
	EXPECT_EQ(system.ram[0x1FD], 0b11011111);
	EXPECT_EQ(system.cpu.SP, 0xFC);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      NOP                                                                                              NOP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(NOP_TEST, CorrectlyDoesNothing) {
	// 1 Bytes, 2 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_NOP;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(system.cpu.P, 0b00000000);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      RTI                                                                                              RTI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(RTI_TEST, CorrectlyLoadsProgramCounter) {
	// 1 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0xA000;
	system.cpu.SP = 0xFC;

	// Initialize memory
	system.ram[0xA000] = INS_RTI;

	system.ram[0x1FF] = 0x80;
	system.ram[0x1FE] = 0x02;
	system.ram[0x1FD] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
}

TEST(RTI_TEST, CorrectlyLoadsProcessorStatus) {
	// 1 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0xA000;
	system.cpu.SP = 0xFC;

	// Initialize memory
	system.ram[0xA000] = INS_RTI;

	system.ram[0x1FF] = 0x80;
	system.ram[0x1FE] = 0x02;
	system.ram[0x1FD] = 0b11001111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0b11001111);

}

TEST(RTI_TEST, ClearsBreakFlag) {
	// 1 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0xA000;
	system.cpu.SP = 0xFC;

	// Initialize memory
	system.ram[0xA000] = INS_RTI;

	system.ram[0x1FF] = 0x80;
	system.ram[0x1FE] = 0x02;
	system.ram[0x1FD] = 0b11011111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0b11001111);
}

TEST(RTI_TEST, CorrectlyPullsInfoFromStack) {
	// 1 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.PC = 0xA000;
	system.cpu.SP = 0xFC;

	// Initialize memory
	system.ram[0xA000] = INS_RTI;

	system.ram[0x1FF] = 0x80;
	system.ram[0x1FE] = 0x02;
	system.ram[0x1FD] = 0b11011111;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0b11001111);
	EXPECT_EQ(system.ram[0x1FF], 0x80);
	EXPECT_EQ(system.ram[0x1FE], 0x02);
	EXPECT_EQ(system.ram[0x1FD], 0b11011111);
	EXPECT_EQ(system.cpu.SP, 0xFF);
}