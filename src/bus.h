#pragma once
#include "ram.h"
#include "MOS6502.h"

class Bus
{
public:
	Bus();
	~Bus();


public: // Components
	MOS6502 cpu;
	Memory ram;
	uint8_t directRam[32 * 1024]; // I should use this instead of a dedicated ram object, all mem methods can be handled by bus or cpu or both
	// Program ROM
	//     header: 1 byte, indicating number of chunks of rom data
	// I/O devices

public: // Read and Write methods
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);
};