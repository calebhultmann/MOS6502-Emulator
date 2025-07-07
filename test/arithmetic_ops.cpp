#include <gtest/gtest.h>
#include "MOS6502.h"
#include "bus.h"
#include "instructions.h"

/*----------------------------------------------------------------------------------------------------------------*/
/*      ADC                                                                                              ADC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(ADC_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_ADC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ADC_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_ADC_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_ADC_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_ADC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_ADC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_ADC_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0xF3;

	// Initialize memory
	system.rom[0] = INS_ADC_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x20;

	// Initialize memory
	system.rom[0] = INS_ADC_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF1;

	// Initialize memory
	system.rom[0] = INS_ADC_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0x20;

	// Initialize memory
	system.rom[0] = INS_ADC_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0xF0;

	// Initialize memory
	system.rom[0] = INS_ADC_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x0;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(ADC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x8F;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 1;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0x90);
}

TEST(ADC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

TEST(ADC_TEST, SetsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0xF0;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x2B;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
	EXPECT_EQ(system.cpu.A, 0x1B);
}

TEST(ADC_TEST, ClearsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7C);
}

TEST(ADC_TEST, SetsOverflowFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x84;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x84;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C | system.cpu.V);
	EXPECT_EQ(system.cpu.A, 0x08);
}

TEST(ADC_TEST, ClearsOverflowFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.V;

	// Initialize memory
	system.rom[0] = INS_ADC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x7B);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      SBC                                                                                              SBC      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(SBC_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x84;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF5;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x84;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF3;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0x84;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0xF3;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0x20;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.X = 0xF1;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0x20;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.Y = 0xF0;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x20;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x20;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z);
	EXPECT_EQ(system.cpu.A, 0);
}

TEST(SBC_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;
	system.cpu.P |= system.cpu.Z;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x23);
}

TEST(SBC_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x90;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x0F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0x81);
}

TEST(SBC_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x40;
	system.cpu.P |= system.cpu.N;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x30;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x10);
}

TEST(SBC_TEST, SetsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x20;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x30;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C | system.cpu.N);
	EXPECT_EQ(system.cpu.A, 0xF0);
}

TEST(SBC_TEST, ClearsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x40;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x30;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x10);
}

TEST(SBC_TEST, SetsOverflowFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x80;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x0F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.V);
	EXPECT_EQ(system.cpu.A, 0x71);
}

TEST(SBC_TEST, ClearsOverflowFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x40;
	system.cpu.P |= system.cpu.V;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_SBC_IM;
	system.rom[1] = 0x30;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, 0);
	EXPECT_EQ(system.cpu.A, 0x10);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CMP                                                                                              CMP      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CMP_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CMP_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, ZeroPageX) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_CMP_ZPX;
	system.rom[1] = 0x10;
	system.ram[0x94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, ZeroPageX_WithWrapAround) {
	// 2 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.X = 0xF5;

	// Initialize memory
	system.rom[0] = INS_CMP_ZPX;
	system.rom[1] = 0xD0;
	system.ram[0xC5] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CMP_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, AbsoluteX) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.X = 0x84;

	// Initialize memory
	system.rom[0] = INS_CMP_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, AbsoluteX_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.X = 0xF3;

	// Initialize memory
	system.rom[0] = INS_CMP_ABSX;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, AbsoluteY) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.Y = 0x84;

	// Initialize memory
	system.rom[0] = INS_CMP_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E94] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, AbsoluteY_WithPageCross) {
	// 3 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.Y = 0xF3;

	// Initialize memory
	system.rom[0] = INS_CMP_ABSY;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7F03] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, IndirectX) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.X = 0x20;

	// Initialize memory
	system.rom[0] = INS_CMP_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x5B] = 0x10;
	system.ram[0x5C] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, IndirectX_WithWrapAround) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.X = 0xF1;

	// Initialize memory
	system.rom[0] = INS_CMP_INDX;
	system.rom[1] = 0x3B;
	system.ram[0x2C] = 0x10;
	system.ram[0x2D] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, IndirectY) {
	// 2 Bytes, 5 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.Y = 0x20;

	// Initialize memory
	system.rom[0] = INS_CMP_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7E30] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(5);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, IndirectY_WithPageCross) {
	// 2 Bytes, 6 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.Y = 0xF0;

	// Initialize memory
	system.rom[0] = INS_CMP_INDY;
	system.rom[1] = 0x30;
	system.ram[0x30] = 0x10;
	system.ram[0x31] = 0x7E;
	system.ram[0x7F00] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(6);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z | system.cpu.C);
}

TEST(CMP_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x8C;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x9C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CMP_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4C;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

TEST(CMP_TEST, SetsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x4F;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

TEST(CMP_TEST, ClearsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.A = 0x2C;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_CMP_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CPX                                                                                              CPX      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CPX_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPX_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPX_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPX_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPX_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPX_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z | system.cpu.C);
}

TEST(CPX_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x2C;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPX_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x8C;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x9C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPX_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4C;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

TEST(CPX_TEST, SetsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x4F;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

TEST(CPX_TEST, ClearsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.X = 0x2C;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_CPX_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

/*----------------------------------------------------------------------------------------------------------------*/
/*      CPY                                                                                              CPY      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(CPY_TEST, Immediate) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPY_TEST, ZeroPage) {
	// 2 Bytes, 3 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPY_ZP;
	system.rom[1] = 0x10;
	system.ram[0x10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(3);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPY_TEST, Absolute) {
	// 3 Bytes, 4 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPY_ABS;
	system.rom[1] = 0x10;
	system.rom[2] = 0x7E;
	system.ram[0x7E10] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(4);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8003);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPY_TEST, SetsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x2C;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.Z | system.cpu.C);
}

TEST(CPY_TEST, ClearsZeroFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x2C;
	system.cpu.P |= system.cpu.Z;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPY_TEST, SetsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x8C;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x9C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}

TEST(CPY_TEST, ClearsNegativeFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4C;
	system.cpu.P |= system.cpu.N;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

TEST(CPY_TEST, SetsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x4F;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x2C;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.C);
}

TEST(CPY_TEST, ClearsCarryFlag) {
	// 2 Bytes, 2 Cycles

	// Initialize system
	Bus system;
	system.cpu.Y = 0x2C;
	system.cpu.P |= system.cpu.C;

	// Initialize memory
	system.rom[0] = INS_CPY_IM;
	system.rom[1] = 0x4F;

	// Run the expected number of cycles
	int status = system.cpu.Run(2);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(system.cpu.P, system.cpu.N);
}