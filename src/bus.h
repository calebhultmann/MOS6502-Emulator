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
	uint8_t ram[32 * 1024]; // 0x0000 - 0x7FFF
	uint8_t rom[16 * 1024]; // 0x8000 - 0xBFFF
	uint8_t vectors[6];     // 0xFFFA - 0xFFFF
	// Program ROM
	//     header: 1 byte, indicating number of chunks of rom data
	// I/O devices

/*
Memory layout:

0x0000 ----- 0x7FFF - 0x8000 ----- 0xBFFF - 0xC000 ----------------- 0xFFF0- 0xFFFA - 0xFFFF
   |  32KB ram  |        |  16KB rom  |        |         unused        |        | vectors |
   ----------------------------------------------------------------------------------------
*/

public: // Read and Write methods
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);
};