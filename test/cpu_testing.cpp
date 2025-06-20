#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

/* Testing framework
TEST(___, ___) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[_] = INS____;

	// Run the expected number of cycles
	cpu.Run(_);

	// Ensure correctness of the results
	EXPECT_EQ(_, _);
}
*/

TEST(LDA_TEST, LDA_Immediate) {
	CPU cpu;
	cpu.Reset();
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x42;

	cpu.Run(2);

	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction (increments to 0x203 due to trying to fetch another instruction


	EXPECT_EQ(cpu.A, 0x42); // Check if accumulator A has the value 0x42
}

TEST(LDA_TEST, LDA_ZeroPage) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ZP;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(3);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}