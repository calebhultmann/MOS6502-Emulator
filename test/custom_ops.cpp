#include <gtest/gtest.h>
#include "MOS6502.h"
#include "bus.h"
#include <iostream>

// custom cout override to test PRT stdout output
class coutCapture {
public:
	coutCapture() {
		oldBuf = std::cout.rdbuf(captureBuffer.rdbuf());
	}

	~coutCapture() {
		std::cout.rdbuf(oldBuf);
	}

	std::string str() const {
		return captureBuffer.str();
	}

private:
	std::stringstream captureBuffer;
	std::streambuf* oldBuf = nullptr;
};

/*----------------------------------------------------------------------------------------------------------------*/
/*      PRT                                                                                              PRT      */
/*----------------------------------------------------------------------------------------------------------------*/
TEST(PRT_TEST, CorrectCycles) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;
	
	// Initialize memory
	system.rom[0] = INS_PRT;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
}

TEST(PRT_TEST, PrintsNumberCharacter) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.terminal_data[0] = (uint8_t)'A';
	system.custom_flags[ASCII_FLAG] = 0;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "65");
}

TEST(PRT_TEST, PrintsASCIICharacter) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.terminal_data[0] = (uint8_t)'A';
	system.custom_flags[0] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "A");
}