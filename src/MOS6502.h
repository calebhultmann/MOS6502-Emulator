#pragma once
#include <stdint.h>

class Memory;

class MOS6502 {

public:

private:
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

	// Components
	int32_t Cycles;
	Memory* ram = nullptr;

	void ConnectRam(Memory* m) { ram = m; }



};