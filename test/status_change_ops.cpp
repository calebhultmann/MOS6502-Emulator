#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLC                                                                                              CLC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLC_TEST, ClearsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.C;

	// Initialize memory
	cpu.mem[0x200] = INS_CLC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLD                                                                                              CLD      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLD_TEST, ClearsDecimalFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.D;

	// Initialize memory
	cpu.mem[0x200] = INS_CLD;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLI                                                                                              CLI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLI_TEST, ClearsInterruptFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.I;

	// Initialize memory
	cpu.mem[0x200] = INS_CLI;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CLV                                                                                              CLV      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CLC_TEST, ClearsOverflowFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.P |= cpu.V;

	// Initialize memory
	cpu.mem[0x200] = INS_CLV;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, 0);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SEC                                                                                              SEC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SEC_TEST, SetsCarryFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_SEC;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.C);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SED                                                                                              SED      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SED_TEST, SetsDecimalFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_SED;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.D);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SEI                                                                                              SEI      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SEI_TEST, SetsInterruptFlag) {
	// 1 Bytes, 2 Cycles

	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_SEI;

	// Run the expected number of cycles
	int status = cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(cpu.PC, 0x201);
	EXPECT_EQ(cpu.P, cpu.I);
}