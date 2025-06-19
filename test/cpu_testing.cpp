#include <gtest/gtest.h>
#include "emulator.h"
#include "instructions.h"

TEST(LDA_TEST, LDA_Immediate) {
	CPU cpu;
	cpu.Reset();

	cpu.mem[0x200] = INS_LDA_IM;
	cpu.mem[0x201] = 0x42;

	cpu.Run();
	EXPECT_EQ(cpu.A, 0x42); // Check if accumulator A has the value 0x42
	EXPECT_EQ(cpu.PC, 0x202); // Check if program counter PC has moved to the next instruction
}

//TEST(CalculatorTest, Add) {
//    Calculator calc;
//    EXPECT_EQ(calc.add(2, 3), 5);
//    EXPECT_EQ(calc.add(-2, 3), 1);
//    EXPECT_EQ(calc.add(0, 0), 0);
//}
//
//TEST(CalculatorTest, Sub) {
//    Calculator calc;
//    EXPECT_EQ(calc.sub(5, 3), 2);
//    EXPECT_EQ(calc.sub(3, 5), -2);
//    EXPECT_EQ(calc.sub(0, 0), 0);
//}
//
//TEST(CalculatorTest, Mul) {
//    Calculator calc;
//    EXPECT_EQ(calc.mul(2, 3), 6);
//    EXPECT_EQ(calc.mul(-2, 3), -6);
//    EXPECT_EQ(calc.mul(0, 5), 0);
//}
//
//TEST(CalculatorTest, Div) {
//    Calculator calc;
//    EXPECT_EQ(calc.div(6, 3), 2);
//    EXPECT_EQ(calc.div(5, 2), 2);
//}
//
//TEST(CalculatorTest, Mod) {
//    Calculator calc;
//    EXPECT_EQ(calc.mod(6, 4), 2);
//    EXPECT_EQ(calc.mod(5, 2), 1);
//}