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

// Execute the current instruction
void MOS6502::ExecuteOperation(Operation operation) {
	switch (operation.instruction) {
	case Instruction::INVALID:
		return;
	case Instruction::LDA:
		A = FetchData(operation);
		UpdateZNFlags(A);
		return;
	case Instruction::LDX:
		X = FetchData(operation);
		UpdateZNFlags(X);
		return;
	case Instruction::LDY:
		Y = FetchData(operation);
		UpdateZNFlags(Y);
		return;
	case Instruction::STA:
		WriteByte(FetchAddress(operation), A);
		return;
	case Instruction::STX:
		WriteByte(FetchAddress(operation), X);
		return;
	case Instruction::STY:
		WriteByte(FetchAddress(operation), Y);
		return;
	case Instruction::TAX:
		Cycles++;
		X = A;
		UpdateZNFlags(X);
		return;
	case Instruction::TAY:
		Cycles++;
		Y = A;
		UpdateZNFlags(Y);
		return;
	case Instruction::TXA:
		Cycles++;
		A = X;
		UpdateZNFlags(A);
		return;
	case Instruction::TYA:
		Cycles++;
		A = Y;
		UpdateZNFlags(A);
		return;
	case Instruction::TSX:
		Cycles++;
		X = SP;
		UpdateZNFlags(X);
		return;
	case Instruction::TXS:
		Cycles++;
		SP = X;
		return;
	case Instruction::PHA:
		PushStack(A);
		return;
	case Instruction::PHP:
		PushStack(P);
		return;
	case Instruction::PLA:
		Cycles++;
		A = PullStack();
		UpdateZNFlags(A);
		return;
	case Instruction::PLP:
		Cycles++;
		P = PullStack();
		UpdateZNFlags(P);
		return;
	case Instruction::AND:
		A = A & FetchData(operation);
		UpdateZNFlags(A);
		return;
	case Instruction::EOR:
		A = A ^ FetchData(operation);
		UpdateZNFlags(A);
		return;
	case Instruction::ORA:
		A = A | FetchData(operation);
		UpdateZNFlags(A);
		return;
	case Instruction::BIT:
	{
		uint8_t data = FetchData(operation);
		uint8_t result = A & data;
		UpdateZNFlags(result);
		SetFlag(V, data & V);
		SetFlag(N, data & N);
		return;
	}
	case Instruction::ADC:
	{
		uint8_t data = FetchData(operation);
		uint16_t result = A + data + (P & C);
		uint8_t byte_result = result & 0xFF;
		SetFlag(V, (A ^ byte_result) & (data ^ byte_result) & N);
		SetFlag(C, result & 0xFF00);
		A = byte_result;
		UpdateZNFlags(A);
		return;
	}
	case Instruction::SBC:
	{
		uint8_t data = FetchData(operation);
		data = ~data;
		uint16_t result = A + data + (P & C);
		uint8_t byte_result = result & 0xFF;
		SetFlag(V, (A ^ byte_result) & (A ^ ~data) & N);
		SetFlag(C, result & 0xFF00);
		A = byte_result;
		UpdateZNFlags(A);
		return;
	}
	case Instruction::CMP:
	{
		uint8_t data = FetchData(operation);
		uint8_t result = A - data;
		UpdateZNFlags(result);
		SetFlag(C, A >= data);
		return;
	}
	case Instruction::CPX:
	{
		uint8_t data = FetchData(operation);
		uint8_t result = X - data;
		UpdateZNFlags(result);
		SetFlag(C, X >= data);
		return;
	}
	case Instruction::CPY:
	{
		uint8_t data = FetchData(operation);
		uint8_t result = Y - data;
		UpdateZNFlags(result);
		SetFlag(C, Y >= data);
		return;
	}
	case Instruction::INC:
	{
		Cycles += 3;
		uint16_t addr = FetchAddress(operation);
		uint8_t data = ReadByte(addr);
		data++;
		WriteByte(addr, data);
		UpdateZNFlags(data);
		return;
	}
	case Instruction::INX:
		Cycles++;
		X++;
		UpdateZNFlags(X);
		return;
	case Instruction::INY:
		Cycles++;
		Y++;
		UpdateZNFlags(Y);
		return;
	case Instruction::DEC:
	{
		Cycles += 3;
		uint16_t addr = FetchAddress(operation);
		uint8_t data = ReadByte(addr);
		data--;
		WriteByte(addr, data);
		UpdateZNFlags(data);
		return;
	}
	case Instruction::DEX:
		Cycles++;
		X--;
		UpdateZNFlags(X);
		return;
	case Instruction::DEY:
		Cycles++;
		Y--;
		UpdateZNFlags(Y);
		return;
	case Instruction::ASL:
	{
		Cycles++;
		if (operation.mode == ACCUMULATOR) {
			SetFlag(C, A & N);
			A <<= 1;
			UpdateZNFlags(A);
		}
		else {
			uint16_t addr = FetchAddress(operation);
			uint8_t data = ReadByte(addr);
			SetFlag(C, data & N);
			data <<= 1;
			WriteByte(addr, data);
			UpdateZNFlags(data);
		}
		return;
	}
	case Instruction::LSR:
	{
		Cycles++;
		if (operation.mode == ACCUMULATOR) {
			SetFlag(C, A & C);
			A >>= 1;
			UpdateZNFlags(A);
		}
		else {
			uint16_t addr = FetchAddress(operation);
			uint8_t data = ReadByte(addr);
			SetFlag(C, data & C);
			data >>= 1;
			WriteByte(addr, data);
			UpdateZNFlags(data);
		}
		return;
	}
	case Instruction::ROL:
	{
		Cycles++;
		uint8_t carry = P & C;
		if (operation.mode == ACCUMULATOR) {
			SetFlag(C, A & N);
			A = (A << 1) | carry;
			UpdateZNFlags(A);
		}
		else {
			uint16_t addr = FetchAddress(operation);
			uint8_t data = ReadByte(addr);
			SetFlag(C, data & N);
			data = (data << 1) | carry;
			WriteByte(addr, data);
			UpdateZNFlags(data);
		}
		return;
	}
	case Instruction::ROR:
	{
		Cycles++;
		uint8_t carry = (P & C) ? 0x80 : 0;
		if (operation.mode == ACCUMULATOR) {
			SetFlag(C, A & C);
			A = (A >> 1) | carry;
			UpdateZNFlags(A);
		}
		else {
			uint16_t addr = FetchAddress(operation);
			uint8_t data = ReadByte(addr);
			SetFlag(C, data & C);
			data = (data >> 1) | carry;
			WriteByte(addr, data);
			UpdateZNFlags(data);
		}
		return;
	}
	case Instruction::JMP:
	{
		uint16_t jmp_addr;
		if (operation.mode == ABSOLUTE) {
			jmp_addr = FetchWord();
		}
		else {
			uint8_t  ind_low = FetchByte();
			uint16_t ind_high = FetchByte();
			uint16_t low = ReadByte(ind_high | ind_low);
			ind_low++;
			uint16_t high = ReadByte(ind_high | ind_low) << 8;
			jmp_addr = high | low;
		}
		PC = jmp_addr;
		return;
	}
	case Instruction::JSR:
	{
		Cycles += 3;
		uint16_t jmp_addr = FetchAddress(operation);
		WriteByte(0x0100 | SP--, (PC - 1) >> 8);
		WriteByte(0x0100 | SP--, (PC - 1) & 0xFF);
		PC = jmp_addr;
		return;
	}
	case Instruction::RTS:
	{
		Cycles += 5;
		uint16_t newPC = ReadByte(0x0100 | ++SP);
		newPC |= (ReadByte(0x0100 | ++SP) >> 8);
		PC = newPC + 1;
		return;
	}
	case Instruction::BCC:
		MaybeBranch(C, 0);
		return;
	case Instruction::BCS:
		MaybeBranch(C, 1);
		return;
	case Instruction::BEQ:
		MaybeBranch(Z, 1);
		return;
	case Instruction::BMI:
		MaybeBranch(N, 1);
		return;
	case Instruction::BNE:
		MaybeBranch(Z, 0);
		return;
	case Instruction::BPL:
		MaybeBranch(N, 0);
		return;
	case Instruction::BVC:
		MaybeBranch(V, 0);
		return;
	case Instruction::BVS:
		MaybeBranch(V, 1);
		return;
	case Instruction::CLC:
		SetFlag(C, 0);
		Cycles++;
		return;
	case Instruction::CLD:
		SetFlag(D, 0);
		Cycles++;
		return;
	case Instruction::CLI:
		SetFlag(I, 0);
		Cycles++;
		return;
	case Instruction::CLV:
		SetFlag(V, 0);
		Cycles++;
		return;
	case Instruction::SEC:
		SetFlag(C, 1);
		Cycles++;
		return;
	case Instruction::SED:
		SetFlag(C, 1);
		Cycles++;
		return;
	case Instruction::SEI:
		SetFlag(C, 1);
		Cycles++;
		return;
	case Instruction::BRK:
		Cycles += 3;
		(void) FetchByte();
		WriteByte(0x0100 | SP--, PC >> 8);
		WriteByte(0x0100 | SP--, PC & 0xFF);
		SetFlag(B, 1);
		WriteByte(0x0100 | SP--, P);
		PC = ReadWord(0xFFFE);
		return;
	case Instruction::NOP:
		Cycles++;
		return;
	case Instruction::RTI:
	{
		Cycles += 5;
		P = ReadByte(0x0100 | ++SP);
		SetFlag(B, 0);
		uint16_t newPC = ReadByte(0x0100 | ++SP);
		newPC |= (ReadByte(0x0100 | ++SP) << 8);
		PC = newPC;
		return;
	}
	}
}