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

// 2, 2
TEST(LDA_TEST, LDA_Immediate) {
	CPU cpu;
	cpu.Reset();
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x42;

	cpu.Run(2);

	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction (increments to 0x203 due to trying to fetch another instruction

	EXPECT_EQ(cpu.P, 0);
	EXPECT_EQ(cpu.A, 0x42); // Check if accumulator A has the value 0x42
}

// 2, 3
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

// 2, 4
TEST(LDA_TEST, LDA_ZeroPageX) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();
	cpu.X = 0x3F
	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ZPX;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x4F] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 3, 4
TEST(LDA_TEST, LDA_Absolute) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 3, 4
TEST(LDA_TEST, LDA_AbsoluteX) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABSX;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 3, 5
TEST(LDA_TEST, LDA_AbsoluteX_WithPageCross) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABSX;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 3, 4
TEST(LDA_TEST, LDA_AbsoluteY) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 3, 5
TEST(LDA_TEST, LDA_AbsoluteY_WithPageCross) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 2, 6
TEST(LDA_TEST, LDA_IndirectX) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_INDX;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 2, 5
TEST(LDA_TEST, LDA_IndirectY) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 2, 6
TEST(LDA_TEST, LDA_IndirectY_WithPageCross) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

// 3, 4
TEST(LDA_TEST, LDA_SetsZeroFlag) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}

TEST(LDA_TEST, LDA_SetsNegativeFlag) {
	// Initialize CPU
	CPU cpu;
	cpu.Reset();

	// Initialize memory
	cpu.mem[0x200] = INS_LDA_ABS;
	cpu.mem[0x201] = 0x10; // Zero page address
	cpu.mem[0x202] = 0xAF;
	cpu.mem[0xAF10] = 0x1;
	cpu.mem[0x10] = 0x84; // Value at zero page address

	// Run the expected number of cycles
	cpu.Run(4);

	// Ensure correctness of the results
	EXPECT_EQ(cpu.A, 0x84); // Check if accumulator A has the value 0x84
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction
}