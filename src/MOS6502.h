#pragma once
#include <cstdint>

class Bus;

class MOS6502 {

public:
	Bus* bus = nullptr;

private: // CPU R/W methods
	uint8_t  readByte(uint16_t addr);
	uint16_t readWord(uint16_t addr);
	void     writeByte(uint16_t addr, uint8_t data);
	void     writeWord(uint16_t addr, uint16_t data);

	uint8_t  fetchByte();
	uint16_t fetchWord();

	void    pushStack(uint8_t data);
	uint8_t pullStack();

private: // Variables
	// Register
	uint16_t PC; // Program Counter
	uint8_t  SP; // Stack Pointer
	uint8_t  A;  // Accumulator Register
	uint8_t  X;  // X Register
	uint8_t  Y;  // Y Register
	uint8_t  P;  // Processor Status

	// Flags
	const uint8_t C = (1 << 0); // Carry
	const uint8_t Z = (1 << 1); // Zero
	const uint8_t I = (1 << 2); // Interrupt Disable
	const uint8_t D = (1 << 3); // Decimal Mode
	const uint8_t B = (1 << 4); // Break Command
	const uint8_t U = (1 << 5); // Unused
	const uint8_t V = (1 << 6); // Overflow
	const uint8_t N = (1 << 7); // Negative

	int32_t Cycles;


public: // Bus interface
	void ConnectBus(Bus* m) { bus = m; }

private: // Bus methods
	uint8_t busRead(uint16_t addr);
	void    busWrite(uint16_t addr, uint8_t data);


};