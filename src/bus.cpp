#include "bus.h"
#include <iostream>

Bus::Bus() {
	cpu.ConnectBus(this);
	for (auto& i : ram) i = 0xFF;

	// NMI handler (not implemented)
	vectors[0] = 0xFF;
	vectors[1] = 0xFF;

	// Power on reset location (points to start of ROM)
	vectors[2] = 0x00;
	vectors[3] = 0x80;

	// BRK/IRQ handler (not implemented)
	vectors[4] = 0xFF;
	vectors[5] = 0xFF;

	cpu.Reset();
}

Bus::~Bus() {

}


//0x0000-0x7FFF ram 0x8000-0xFFFF rom
void Bus::write(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr <= 0x7FFF)
		ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr) {
	if (addr >= 0x0000 && addr <= 0x7FFF)
		return ram[addr];
	else if (addr >= 0x8000 && addr <= 0xAFFF)
		return rom[addr & 0x3FFF];
	else if (addr >= 0xFFFA && addr <= 0xFFFF)
		return vectors[addr - 0xFFFA];
	return 0;
}