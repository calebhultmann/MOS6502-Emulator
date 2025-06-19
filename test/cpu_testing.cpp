#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

TEST(LDA_TEST, LDA_Immediate) {
	CPU cpu;
	cpu.Reset();
	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x42;

	cpu.Run(0);
	EXPECT_EQ(cpu.A, 0x42); // Check if accumulator A has the value 0x42
	EXPECT_EQ(cpu.PC, 0x203); // Check if program counter PC has moved to the next instruction (increments to 0x203 due to trying to fetch another instruction
}