#include "bus.h"

Bus::Bus() {
	cpu.ConnectBus(this);
	for (auto& i : ram) i = 0xFF;
}

Bus::~Bus() {

}


//0x0000-0x7FFF ram 0x8000-0xFFFF rom
void Bus::write(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr < +0x7FFF)
		ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr) {
	if (addr >= 0x0000 && addr <= 0x7FFF)
		return ram[addr];
	else if (addr >= 0x8000 && addr <= 0xAFFF)
		return rom[addr];
	else if (addr >= 0xFFFA && addr <= 0xFFFF)
		return vectors[addr & 0x6];
	return 0;
}