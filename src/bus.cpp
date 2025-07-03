#include "bus.h"

Bus::Bus() {

}

Bus::~Bus() {

}


//0x0000-0x7FFF ram 0x8000-0xFFFF rom
void Bus::write(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr < +0x7FFF)
		directRam[addr] = data;
}

uint8_t Bus::read(uint16_t addr) {
	if (addr >= 0x0000 && addr < +0x7FFF)
		return directRam[addr];
	return 0;
}