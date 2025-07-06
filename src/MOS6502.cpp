#include "MOS6502.h"
#include "bus.h"

uint8_t MOS6502::readByte(uint16_t addr)
{
	Cycles--;
	return busRead(addr);
}

uint16_t MOS6502::readWord(uint16_t addr)
{
	Cycles -= 2;
	uint16_t low = busRead(addr);
	uint16_t high = busRead(addr + 1);
	return (high << 8) | low;
}

void MOS6502::writeByte(uint16_t addr, uint8_t data)
{
	Cycles--;
	busWrite(addr, data);
}

void MOS6502::writeWord(uint16_t addr, uint16_t data)
{
	Cycles -= 2;
	busWrite(addr, data & 0x00FF);
	busWrite(addr + 1, (data >> 8) & 0x00FF);
}

uint8_t MOS6502::fetchByte()
{
	Cycles--;
	return busRead(PC++);
}

uint16_t MOS6502::fetchWord()
{
	Cycles -= 2;
	uint16_t low = busRead(PC++);
	uint16_t high = busRead(PC++);
	return (high << 8) | low;
}

void MOS6502::pushStack(uint8_t data)
{
	Cycles -= 2;
	busWrite(0x0100 | SP--, data);
}

uint8_t MOS6502::pullStack()
{
	Cycles -= 2;
	uint8_t data = busRead(0x0100 | ++SP);
	busWrite(0x0100 | ++SP, 0xFF);
	return data;
}






uint8_t MOS6502::busRead(uint16_t addr)
{
	return bus->read(addr);
}

void MOS6502::busWrite(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}
