#include "MOS6502.h"
#include "bus.h"
#include "mappings.h"
#include <stdexcept>

// Read from the bus
uint8_t MOS6502::BusRead(uint16_t addr)
{
	return bus->read(addr);
}

// Write to the bus
void MOS6502::BusWrite(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

// Read a byte from a given memory address
uint8_t MOS6502::ReadByte(uint16_t addr)
{
	Cycles++;
	return BusRead(addr);
}

// Read a word from a given memory address
uint16_t MOS6502::ReadWord(uint16_t addr)
{
	Cycles += 2;
	uint16_t low = BusRead(addr);
	uint16_t high = BusRead(addr + 1);
	return (high << 8) | low;
}

// Write a byte to a given memory address
void MOS6502::WriteByte(uint16_t addr, uint8_t data)
{
	Cycles++;
	BusWrite(addr, data);
}

// Write a word to a given memory address
void MOS6502::WriteWord(uint16_t addr, uint16_t data)
{
	Cycles += 2;
	BusWrite(addr, data & 0x00FF);
	BusWrite(addr + 1, (data >> 8) & 0x00FF);
}

// Fetch the next byte from the program counter
uint8_t MOS6502::FetchByte()
{
	Cycles++;
	return BusRead(PC++);
}

// Fetch the next word from the program counter
uint16_t MOS6502::FetchWord()
{
	Cycles += 2;
	uint16_t low = BusRead(PC++);
	uint16_t high = BusRead(PC++);
	return (high << 8) | low;
}

// Push a byte to the stack
void MOS6502::PushStack(uint8_t data)
{
	Cycles += 2;
	BusWrite(0x0100 | SP--, data);
}

// Pull a byte from the stack
uint8_t MOS6502::PullStack()
{
	Cycles += 2;
	uint8_t data = BusRead(0x0100 | ++SP);
	BusWrite(0x0100 | ++SP, 0xFF);
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
	int8_t offset = static_cast<int8_t>(FetchByte());
	const uint16_t oldPC = PC;
	PC += offset;
	Cycles++;
	
	if ((PC >> 8) != (oldPC >> 8))
		Cycles++;
}
// Branches if the given flag in the processor status matches the given T/F value
void MOS6502::MaybeBranch(uint8_t flag, bool value) {
	(P & flag) == ((value) ? flag : 0) ? Branch() : (void) FetchByte();
}

// Reset CPU
void MOS6502::Reset() {
	// Confirm: cycles should be reset to 0 on
	Cycles = -2;
	PC = ReadWord(0xFFFC);
	SP = 0xFF;
	P = 0;
	A = X = Y = 0;
}

// Acquires the effective address of the current instruction. Useful for instructions that write to memory
uint16_t MOS6502::FetchAddress(Operation operation) {
	switch (operation.mode) {
	case RELATIVE:
		return PC + FetchByte(); // Check this works with signed numbers
	case IMMEDIATE:
		return ++PC; // Check if this is even used let alone if its correct (i dont think the answer to either is yes)
	case ABSOLUTE:
		return FetchWord();
	case ZERO_PAGE:
		return 0x0000 | FetchByte();
	case ABS_INDIRECT:
	{
		uint16_t abs_addr = FetchWord();
		return ReadWord(abs_addr);
	}
	case X_ABSOLUTE:
		Cycles++;
		return FetchWord() + X;
	case Y_ABSOLUTE:
		Cycles++;
		return FetchWord() + Y;
	case X_ZERO_PAGE:
	{
		Cycles++;
		uint8_t ZPByte = FetchByte() + X;
		return 0x0000 | ZPByte;
	}
	case Y_ZERO_PAGE:
	{
		Cycles++;
		uint8_t ZPByte = FetchByte() + Y;
		return 0x0000 | ZPByte;
	}
	case X_INDEX_ZP_INDIRECT:
	{
		Cycles++;
		uint8_t ZPByte = FetchByte() + X;
		return ReadWord(0x0000 | ZPByte);
	}
	case ZP_INDIRECT_Y_INDEX: // is this used? must be yeah?
		Cycles++;
		return ReadWord(0x0000 | FetchByte()) + Y;
	}
	return 0; // Default return value, should not be reached
}

// Fetch data for the current instruction based on address mode
uint8_t MOS6502::FetchData(Operation operation) {
	switch (operation.mode) {
	case ACCUMULATOR:
		return A;
	case IMMEDIATE:
		return FetchByte();
	case X_ABSOLUTE:
	{
		uint16_t addr = FetchWord();
		uint8_t high = addr >> 8;
		addr += X;
		if (addr >> 8 != high)
			Cycles++;
		return ReadByte(addr);
	}
	case Y_ABSOLUTE:
	{
		uint16_t addr = FetchWord();
		uint8_t high = addr >> 8;
		addr += Y;
		if (addr >> 8 != high)
			Cycles++;
		return ReadByte(addr);
	}
	case ZP_INDIRECT_Y_INDEX:
	{
		uint16_t ind_addr = ReadWord(0x0000 | FetchByte());
		uint8_t high = ind_addr >> 8;
		ind_addr += Y;
		if (ind_addr >> 8 != high)
			Cycles++;
		return ReadByte(ind_addr);
	}
	default:
		return ReadByte(FetchAddress(operation));
	}
}

// Fetch the next operation from memory
Operation MOS6502::FetchOperation() {
	uint8_t opcode = FetchByte();
	Operation operation;
	try {
		operation = instruction_opcode_bimap.right.at(opcode);
	}
	catch (std::out_of_range& e) {
		operation = Operation{ Instruction::INVALID, UNKNOWN };
	}
	return operation;
}