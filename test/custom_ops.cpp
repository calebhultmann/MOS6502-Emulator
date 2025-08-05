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

TEST(PRT_TEST, PrintsNumberAsNumber) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.terminal_buffer[0] = (uint8_t)200;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "200");
}

TEST(PRT_TEST, PrintsCharAsNumber) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.terminal_buffer[0] = (uint8_t)'A';

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "65");
}

TEST(PRT_TEST, PrintsNumberAsChar) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.terminal_buffer[0] = (uint8_t)65;
	system.custom_flags[ASCII_FLAG] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "A");
}

TEST(PRT_TEST, PrintsCharAsChar) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.terminal_buffer[0] = (uint8_t)'A';
	system.custom_flags[ASCII_FLAG] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "A");
}

TEST(PRT_TEST, PrintsMultipleNumbers) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	for (int i = 0; i < 8; i++) {
		system.terminal_buffer[i] = (uint8_t)i;
	}

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "01234567");
}

TEST(PRT_TEST, PrintsAllNumbers) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	for (int i = 0; i < 16; i++) {
		system.terminal_buffer[i] = (uint8_t)i;
	}

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "0123456789101112131415");
}

TEST(PRT_TEST, PrintsMultipleChars) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	char str[] = "Hello, World!";
	for (int i = 0; i < 13; i++) {
		system.terminal_buffer[i] = (uint8_t)str[i];
	}
	system.custom_flags[ASCII_FLAG] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "Hello, World!");
}

TEST(PRT_TEST, PrintsAllChars) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	char str[] = "aAbBcCdDeEfFgGhH";
	for (int i = 0; i < 16; i++) {
		system.terminal_buffer[i] = (uint8_t)str[i];
	}
	system.custom_flags[ASCII_FLAG] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "aAbBcCdDeEfFgGhH");
}

TEST(PRT_TEST, PrintsNewLines) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	char str[] = "Line 1!\nLine 2!";
	for (int i = 0; i < 15; i++) {
		system.terminal_buffer[i] = (uint8_t)str[i];
	}
	system.custom_flags[ASCII_FLAG] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8001);
	EXPECT_EQ(capture.str(), "Line 1!\nLine 2!");
}

TEST(PRT_TEST, ClearsTerminalBuffer) {
	// 1 Byte, 34 Cycles

	// Initialize system
	Bus system;

	// Initialize memory
	system.rom[0] = INS_PRT;
	system.rom[1] = INS_PRT;

	char str[] = "blahblah";
	for (int i = 0; i < 8; i++) {
		system.terminal_buffer[i] = (uint8_t)str[i];
	}
	system.custom_flags[ASCII_FLAG] = 1;

	// Capture std::cout during CPU run
	coutCapture capture;

	// Run the expected number of cycles
	int status = system.cpu.Run(34);
	EXPECT_EQ(capture.str(), "blahblah");
	status = system.cpu.Run(34);

	// Check test correctness
	EXPECT_EQ(status, 0);
	EXPECT_EQ(system.cpu.PC, 0x8002);
	EXPECT_EQ(capture.str(), "blahblah");
}