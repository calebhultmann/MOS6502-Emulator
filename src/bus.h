#pragma once
#include "MOS6502.h"
#include <cstdint>

class Bus
{
public:
	Bus();
	~Bus();


public: // Components
	MOS6502 cpu;
	uint8_t ram[32 * 1024];
	uint8_t rom[16 * 1024];
	uint8_t vectors[6];
	// Program ROM
	//     header: 1 byte, indicating number of chunks of rom data
	// I/O devices

public: // Read and Write methods
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);
};