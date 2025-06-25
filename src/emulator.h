#pragma once

#include "instructions.h"
#include "mappings.h"
#include <stdexcept>

using SByte = int8_t;
using Byte = uint8_t;
using Word = uint16_t;
using u32 = uint32_t;
using s32 = int32_t;

struct Mem
{
    // 64KB memory
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    // Set all memory bytes to 0x00, initialize start vector at 0xFFFC/0xFFFD to 0x0200
    void initialize()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i] = 0xFF;
        }
        Data[0xFFFC] = 0x00;
        Data[0xFFFD] = 0x02;
    }

    // Read 1 byte
    Byte operator[](Word Address) const
    {
        return Data[Address];
    }

    // Write 1 byte
    Byte& operator[](Word Address)
    {
        return Data[Address];
    }

    // Read a byte from a memory address
    Byte ReadByte(s32& Cycles, Word Address)
    {
        Byte Value = Data[Address];
        Cycles--;
        return Value;
    }

    // Read a word (2 bytes) from a memory address
    Word ReadWord(s32& Cycles, Word Address)
    {
        Word Value = Data[Address];
        Address++;
        Value |= (Data[Address] << 8);
		Cycles -= 2;
        return Value;
    }

    // Fetch a byte from the program counter and increment it
    Byte FetchByte(s32& Cycles, Word& PC)
    {
        Byte Value = Data[PC];
        PC++;
        Cycles--;
        return Value;
    }

    // Fetch a word (2 bytes) from the program counter and increment it
    Word FetchWord(s32& Cycles, Word& PC)
    {
        Word Value = Data[PC];
        PC++;
        Value |= (Data[PC] << 8);
        PC++;
        Cycles -= 2;
        return Value;
    }

    // Write a byte to a memory address
    void WriteByte(s32& Cycles, Word Address, Byte Value)
    {
        Data[Address] = Value;
        Cycles--;
    }

    // Write a word (2 bytes) to a memory address
    void WriteWord(s32& Cycles, Word Address, Word Value)
    {
        Data[Address] = Value & 0xFF;
        Data[Address + 1] = (Value >> 8) & 0xFF;
        Cycles -= 2;
    }

    // Push a byte onto the stack
    void PushStack(s32& Cycles, Byte& SP, Byte Value)
    {
        Data[0x100 | SP--] = Value;
		Cycles -= 2;
    }

    // Pull a byte from the stack
    Byte PullStack(s32& Cycles, Byte& SP)
    {
        Byte Value = Data[0x100 | ++SP];
        Data[0x100 | SP] = 0xFF;
		Cycles -= 2;
        return Value;
    }
};

struct CPU
{
    Word PC; // Program Counter
    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y
    Byte S;  // Stack Pointer
    Byte P;  // Processor Status

    const Byte C = 0b00000001; // Carry Flag
    const Byte Z = 0b00000010; // Zero Flag
    const Byte I = 0b00000100; // Interrupt Disable Flag
    const Byte D = 0b00001000; // Decimal Mode Flag
    const Byte B = 0b00010000; // Break Command Flag
    const Byte V = 0b01000000; // Overflow Flag
    const Byte N = 0b10000000; // Negative Flag

    s32 Cycles;
    Mem mem;

    // Sets a given flag in the processor status register
    void SetFlag(Byte flag) {
        P |= flag;
    }

    // Clears a given flag in the processor status register
    void ClearFlag(Byte flag) {
        P &= ~flag;
    }

    // Set the Z and N flags with respect to a byte of data; Very common result of many opcodes
    void RegisterSetZNStatus(Byte Data)
    {
        P = (P & ~Z) | ((Data == 0) * Z);
        P = (P & ~N) | (Data & N);
    }

    // Turn a zero-page byte into a workable 16-bit address
    Word ZPByteToAddress(Byte ZPByte)
    {
        return (0x0000 | ZPByte);
    }

	// Branch to a new address based on the current program counter and an offset
    void Branch() {
        Byte offset = mem.FetchByte(Cycles, PC);
        const Word oldPC = PC;
        PC += static_cast<SByte>(offset);
        Cycles--;

        const bool PageCross = (PC >> 8) != (oldPC >> 8);
        if (PageCross)
        {
            Cycles--;
        }
    }

	// Branches if the given flag in the processor status matches the given value
    void MaybeBranch(Byte flag, Byte value) {
        (P & flag) == value ? Branch() : (void) mem.FetchByte(Cycles, PC);
    }

    // Reset CPU
    void Reset()
    {
        mem.initialize();
        PC = (mem[0xFFFC] | (mem[0xFFFD] << 8));
        S = 0xFF;
        P = 0;
        A = X = Y = 0;
    }

    // Copy/import from an external Memory object into the CPUs internal memory
    void ImportCode(Mem& extMem)
    {
        for (u32 i = 0; i < mem.MAX_MEM; i++)
        {
            mem.Data[i] = extMem.Data[i];
        }
    }

    // Acquires the effective address of the current instruction. Useful for instructions that write to memory
    Word FetchAddress(Operation operation) {
        AddressMode mode = operation.mode;
        switch (mode) {
        case RELATIVE:
        {
            SByte offset = mem.FetchByte(Cycles, PC);
            return PC + offset; // DOES THIS WORK WITH SIGNED NUMBERS?
        }
        case IMMEDIATE:
            return ++PC;
        case ABSOLUTE:
            return mem.FetchWord(Cycles, PC);
        case ZERO_PAGE:
        {
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            return ZPByteToAddress(ZPByte);
        }
        case ABS_INDIRECT:
        {
            Word absolute_address = mem.FetchWord(Cycles, PC);
            return mem.ReadWord(Cycles, absolute_address);
        }
        case X_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
			addr += X;
			Cycles--;
            return addr;
        }
        case Y_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            addr += Y;
            Cycles--;
            return addr;
        }
        case X_ZERO_PAGE:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(ZPBYte);
			ZPAddr += X;
			Cycles--;
			(ZPAddr & 0xFF00) ? ZPAddr &= 0x00FF : ZPAddr;
            return ZPAddr;
        }
        case Y_ZERO_PAGE:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(ZPBYte);
            ZPAddr += Y;
            Cycles--;
            (ZPAddr & 0xFF00) ? ZPAddr &= 0x00FF : ZPAddr;
            return ZPAddr;
        }
        case X_INDEX_ZP_INDIRECT:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(ZPBYte);
            ZPAddr += X;
			Cycles--;
            (ZPAddr & 0xFF00) ? ZPAddr &= 0x00FF : ZPAddr;
            return mem.ReadWord(Cycles, ZPAddr);
        }
        case ZP_INDIRECT_Y_INDEX:
        {
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(ZPByte);
            Word indirect_addr = mem.ReadWord(Cycles, ZPAddr);
            indirect_addr += Y;
            Cycles--;
            return indirect_addr;
        }
        }
        throw std::runtime_error("Invalid address mode encountered while fetching data.");
        return 0; // Default return value, should not be reached
    }

    // Fetch data for the current instruction based on address mode
    Byte FetchData(Operation operation) {
        AddressMode mode = operation.mode;
        switch (mode) {
        case ACCUMULATOR:
            return A;
        case IMMEDIATE:
            return mem.FetchByte(Cycles, PC);
        case X_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            Byte high = (addr >> 8) & 0xFF;
            addr += X;
            (addr >> 8 != high) ? Cycles-- : Cycles;
            return mem.ReadByte(Cycles, addr);
        }
        case Y_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            Byte high = (addr >> 8) & 0xFF;
            addr += Y;
            (addr >> 8 != high) ? Cycles-- : Cycles;
            return mem.ReadByte(Cycles, addr);
        }
        case ZP_INDIRECT_Y_INDEX:
        {
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(ZPByte);
            Word indirect_addr = mem.ReadWord(Cycles, ZPAddr);
            Byte high = (indirect_addr >> 8) & 0xFF;
            indirect_addr += Y;
            (indirect_addr >> 8 != high) ? Cycles-- : Cycles;
            return mem.ReadByte(Cycles, indirect_addr);
        }
        default:
			return mem.ReadByte(Cycles, FetchAddress(operation));        
        }
    }

    // Fetch the next operation from memory
    Operation FetchOperation() {
        Byte Opcode = mem.FetchByte(Cycles, PC);
        Operation operation;
        try {
            operation = instruction_opcode_bimap.right.at(Opcode);
        }
        catch (std::out_of_range& e) {
            //std::cout << "Unrecognized opcode: " << std::hex << (int)Opcode << std::dec << std::endl;
            operation = Operation{ Instruction::INVALID, UNKNOWN };
        }
        return operation;
    }

    // Execute the current instruction
    void ExecuteOperation(Operation operation) {
        Instruction instruction = operation.instruction;
        switch (instruction) {
        case Instruction::INVALID:
            return;
        case Instruction::LDA:
            A = FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case Instruction::LDX:
            X = FetchData(operation);
            RegisterSetZNStatus(X);
            return;
        case Instruction::LDY:
            Y = FetchData(operation);
            RegisterSetZNStatus(Y);
            return;
        case Instruction::STA:
        {
            Word addr = FetchAddress(operation);
            mem.WriteByte(Cycles, addr, A);
            return;
        }
        case Instruction::STX:
        {
            Word addr = FetchAddress(operation);
            mem.WriteByte(Cycles, addr, X);
            return;
        }
        case Instruction::STY:
        {
            Word addr = FetchAddress(operation);
            mem.WriteByte(Cycles, addr, Y);
            return;
        }
        case Instruction::TAX:
            X = A;
            Cycles--;
            RegisterSetZNStatus(X);
            return;
        case Instruction::TAY:
            Y = A;
            Cycles--;
            RegisterSetZNStatus(Y);
            return;
        case Instruction::TXA:
            A = X;
            Cycles--;
            RegisterSetZNStatus(A);
            return;
        case Instruction::TYA:
            A = Y;
            Cycles--;
            RegisterSetZNStatus(A);
            return;
        case Instruction::TSX:
            X = S;
            Cycles--;
            RegisterSetZNStatus(X);
            return;
        case Instruction::TXS:
            S = X;
            Cycles--;
            return;
        case Instruction::PHA:
            mem.PushStack(Cycles, S, A);
            return;
        case Instruction::PHP:
            mem.PushStack(Cycles, S, P);
            return;
        case Instruction::PLA:
            A = mem.PullStack(Cycles, S);
            Cycles--;
            RegisterSetZNStatus(A);
            return;
        case Instruction::PLP:
            P = mem.PullStack(Cycles, S);
            Cycles--;
            return;
        case Instruction::AND:
            A = A & FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case Instruction::EOR:
            A = A ^ FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case Instruction::ORA:
            A = A | FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case Instruction::BIT:
        {
			Byte data = FetchData(operation);
            Byte result = A & data;
            RegisterSetZNStatus(result);
			((data & V) > 0) ? SetFlag(V) : ClearFlag(V);
			((data & N) > 0) ? SetFlag(N) : ClearFlag(N);
            return;
        }
        case Instruction::ADC:
        {
            Byte data = FetchData(operation);
            Byte similar_sign = ~((data & N) ^ (A & N));
            A += (data + (P & C));
            if ((similar_sign & N) != (A & N)) {
                SetFlag(C);
                SetFlag(V);
            }
            else {
                ClearFlag(C);
                ClearFlag(V);
            }
            RegisterSetZNStatus(A);
        }
        case Instruction::SBC: // NOT DONE
        case Instruction::CMP: // NOT DONE
        case Instruction::CPX: // NOT DONE
        case Instruction::CPY: // NOT DONE
        case Instruction::INC:
        {
            Word addr = FetchAddress(operation);
            RegisterSetZNStatus(++mem[addr]);
            Cycles -= 3;
            return;
        }
        case Instruction::INX:
            X++;
			Cycles--;
            RegisterSetZNStatus(X);
            return;
        case Instruction::INY:
            Y++;
			Cycles--;
            RegisterSetZNStatus(Y);
            return;
        case Instruction::DEC:
        {
            Word addr = FetchAddress(operation);
            RegisterSetZNStatus(--mem[addr]);
            Cycles -= 3;
            return;
        }
        case Instruction::DEX:
            X--;
            Cycles--;
            RegisterSetZNStatus(X);
            return;
        case Instruction::DEY:
            Y--;
            Cycles--;
            RegisterSetZNStatus(Y);
            return;
        case Instruction::ASL:
        {
            if (operation.mode == ACCUMULATOR) {
				(A & 0x10000000) ? SetFlag(C) : ClearFlag(C);
                A <<= 1;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
				(value & 0x10000000) ? SetFlag(C) : ClearFlag(C);
                value <<= 1;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::LSR:
        {
            if (operation.mode == ACCUMULATOR) {
                (A & 1) ? SetFlag(C) : ClearFlag(C);
                A >>= 1;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                (value & 1) ? SetFlag(C) : ClearFlag(C);
                value >>= 1;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::ROL:
        {
            if (operation.mode == ACCUMULATOR) {
                Byte carry = (P & C) ? 1 : 0;
                (A & N) > 1 ? SetFlag(C) : ClearFlag(C);
                A = (A << 1) | carry;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                Byte carry = (P & C) ? 1 : 0;
                (value & N) > 1 ? SetFlag(C) : ClearFlag(C);
                value = (value << 1) | carry;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::ROR:
        {
            if (operation.mode == ACCUMULATOR) {
                Byte carry = (P & C) ? 0x80 : 0;
                (A & 1) ? SetFlag(C) : ClearFlag(C);
                A = (A >> 1) | carry;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                Byte carry = (P & C) ? 0x80 : 0;
                (value & 1) ? SetFlag(C) : ClearFlag(C);
                value = (value >> 1) | carry;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::JMP:
        {
            Word addr = FetchAddress(operation);
            Word jmp_addr = mem.ReadWord(Cycles, addr);
            PC = jmp_addr;
            return;
        }
        case Instruction::JSR:
        {
            Word addr = FetchAddress(operation);
            Word jmp_addr = mem.ReadWord(Cycles, addr);
            mem.PushStack(Cycles, S, (PC >> 8) & 0xFF);
            mem.PushStack(Cycles, S, PC & 0xFF);
            PC = jmp_addr;
            return;
        }
        case Instruction::RTS:
        {
            Word low = mem.PullStack(Cycles, S);
            Word high = mem.PullStack(Cycles, S);
            Word return_addr = (low | (high << 8));
            PC = return_addr;
            return;
        }
        case Instruction::BCC:
			MaybeBranch(C, 0);
            return;
        case Instruction::BCS:
            MaybeBranch(C, C);
            return;
        case Instruction::BEQ:
			MaybeBranch(Z, Z);
            return;
        case Instruction::BMI:
            MaybeBranch(N, N);
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
            MaybeBranch(V, V);
            return;
        case Instruction::CLC:
            ClearFlag(C);
            return;
        case Instruction::CLD:
            ClearFlag(D);
            return;
        case Instruction::CLI:
            ClearFlag(I);
            return;
        case Instruction::CLV:
            ClearFlag(V);
            return;
        case Instruction::SEC:
            SetFlag(C);
            return;
        case Instruction::SED:
            SetFlag(D);
            return;
        case Instruction::SEI:
            SetFlag(I);
            return;
        case Instruction::BRK:
            mem.PushStack(Cycles, S, (PC >> 8) & 0xFF);
            mem.PushStack(Cycles, S, PC & 0xFF);
            mem.PushStack(Cycles, S, P);
            SetFlag(B);
            PC = mem.ReadWord(Cycles, 0xFFFE);
            return;
        case Instruction::NOP:
            return;
        case Instruction::RTI:
        {
            P = mem.PullStack(Cycles, S);
            Word low = mem.PullStack(Cycles, S);
            Word high = mem.PullStack(Cycles, S);
            S = low | high << 8;
            return;
        }
        }

    }

    // Run the emulator
	//    status > 0 -- overused cycles
    //    status < 0 -- error code
	//    status = 0 -- normal termination
    int Run(s32 CyclesRequested, bool noStop = false)
    {
		Cycles = CyclesRequested;
        int exit_status = 0;
        while (Cycles > 0 || noStop)
        {
            Operation operation = FetchOperation();
            if (operation.instruction == Instruction::INVALID)
            {
                //std::cout << "Unknown operation encountered. Stopping execution." << std::endl;
                return -1;
                break;
            }
            ExecuteOperation(operation);
        }

        if (exit_status != 0) {
            return exit_status;
        }

        if (Cycles < 0 && !noStop) {
            return 0 - Cycles;
        }

        return 0;
    }

};