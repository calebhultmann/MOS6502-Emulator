#include "MOS6502.h"
#include "bus.h"

// Read from the bus
uint8_t MOS6502::busRead(uint16_t addr)
{
	return bus->read(addr);
}

// Write to the bus
void MOS6502::busWrite(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

// Read a byte from a given memory address
uint8_t MOS6502::readByte(uint16_t addr)
{
	Cycles++;
	return busRead(addr);
}

// Read a word from a given memory address
uint16_t MOS6502::readWord(uint16_t addr)
{
	Cycles += 2;
	uint16_t low = busRead(addr);
	uint16_t high = busRead(addr + 1);
	return (high << 8) | low;
}

// Write a byte to a given memory address
void MOS6502::writeByte(uint16_t addr, uint8_t data)
{
	Cycles++;
	busWrite(addr, data);
}

// Write a word to a given memory address
void MOS6502::writeWord(uint16_t addr, uint16_t data)
{
	Cycles += 2;
	busWrite(addr, data & 0x00FF);
	busWrite(addr + 1, (data >> 8) & 0x00FF);
}

// Fetch the next byte from the program counter
uint8_t MOS6502::fetchByte()
{
	Cycles++;
	return busRead(PC++);
}

// Fetch the next word from the program counter
uint16_t MOS6502::fetchWord()
{
	Cycles += 2;
	uint16_t low = busRead(PC++);
	uint16_t high = busRead(PC++);
	return (high << 8) | low;
}

// Push a byte to the stack
void MOS6502::pushStack(uint8_t data)
{
	Cycles += 2;
	busWrite(0x0100 | SP--, data);
}

// Pull a byte from the stack
uint8_t MOS6502::pullStack()
{
	Cycles += 2;
	uint8_t data = busRead(0x0100 | ++SP);
	busWrite(0x0100 | ++SP, 0xFF);
	return data;
}

// Set a given flag to a given T/F value
void MOS6502::SetFlag(uint8_t flag, bool value) {
	(value) ? P |= flag : P &= ~flag;
}

// Set the Z and N flags with respect to a byte of data; Very common result of many opcodes
void MOS6502::UpdateZNFlags(uint8_t data) {
	SetFlag(Z, data == 0);
	SetFlag(N, data & N);
}

// Branch to a new address based on the current program counter and an offset
void MOS6502::Branch() {
	int8_t offset = static_cast<int8_t>(fetchByte());
	const uint16_t oldPC = PC;
	PC += offset;
	Cycles++;
	
	if ((PC >> 8) != (oldPC >> 8))
		Cycles++;
}
// Branches if the given flag in the processor status matches the given T/F value
void MOS6502::MaybeBranch(uint8_t flag, bool value) {
	(P & flag) == ((value) ? flag : 0) ? Branch() : (void) fetchByte();
}

// Reset CPU
void MOS6502::Reset() {
	// Confirm: cycles should be reset to 0 on
	Cycles = -2;
	PC = readWord(0xFFFC);
	SP = 0xFF;
	P = 0;
	A = X = Y = 0;
}