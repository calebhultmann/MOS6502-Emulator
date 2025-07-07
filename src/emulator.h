#pragma once

#include "instructions.h"
#include "mappings.h"
#include <stdexcept>
#include <iostream>

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

};

struct CPU
{

    // Turn a zero-page byte into a workable 16-bit address
    Word ZPByteToAddress(Byte ZPByte)
    {
        return (0x0000 | ZPByte);
    }

    // Copy/import from an external Memory object into the CPUs internal memory
    void ImportCode(Mem& extMem)
    {
        for (u32 i = 0; i < mem.MAX_MEM; i++)
        {
            mem.Data[i] = extMem.Data[i];
        }
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
			Word result = A + data + (P & C);
            Byte byte_result = result & 0xFF;
            ((A ^ byte_result) & (data ^ byte_result) & N) ? SetFlag(V) : ClearFlag(V);
			(result & 0xFF00) ? SetFlag(C) : ClearFlag(C);
			A = result & 0xFF;
            RegisterSetZNStatus(A);
            return;
        }
        case Instruction::SBC:
        {
            Byte data = FetchData(operation);
            data = ~data;
            Word result = A + data + (P & C);
			Byte byte_result = result & 0xFF;
            ((A ^ byte_result) & (A ^ ~data) & N) ? SetFlag(V) : ClearFlag(V);
            (result & 0xFF00) ? ClearFlag(C) : SetFlag(C);
            A = byte_result & 0xFF;
            RegisterSetZNStatus(A);
            return;
        }
        case Instruction::CMP:
        {
            Byte data = FetchData(operation);
            Byte result = A - data;
            RegisterSetZNStatus(result);
            (A >= data) ? SetFlag(C) : ClearFlag(C);
			return;
        }
        case Instruction::CPX:
        {
            Byte data = FetchData(operation);
            Byte result = X - data;
            RegisterSetZNStatus(result);
            (X >= data) ? SetFlag(C) : ClearFlag(C);
            return;
        }
        case Instruction::CPY:
        {
            Byte data = FetchData(operation);
            Byte result = Y - data;
            RegisterSetZNStatus(result);
            (Y >= data) ? SetFlag(C) : ClearFlag(C);
            return;
        }
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
                (A & N) > 0 ? SetFlag(C) : ClearFlag(C);
                A <<= 1;
                Cycles--;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                (value & N) > 0 ? SetFlag(C) : ClearFlag(C);
                value <<= 1;
				Cycles--;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::LSR:
        {
            if (operation.mode == ACCUMULATOR) {
                (A & C) ? SetFlag(C) : ClearFlag(C);
                A >>= 1;
                Cycles--;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                (value & C) ? SetFlag(C) : ClearFlag(C);
                value >>= 1;
                Cycles--;
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
                Cycles--;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                Byte carry = (P & C) ? 1 : 0;
                (value & N) > 1 ? SetFlag(C) : ClearFlag(C);
                value = (value << 1) | carry;
                Cycles--;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::ROR:
        {
            if (operation.mode == ACCUMULATOR) {
                Byte carry = (P & C) ? 0x80 : 0;
                (A & C) ? SetFlag(C) : ClearFlag(C);
                A = (A >> 1) | carry;
                Cycles--;
                RegisterSetZNStatus(A);
            }
            else {
                Word addr = FetchAddress(operation);
                Byte value = mem.ReadByte(Cycles, addr);
                Byte carry = (P & C) ? 0x80 : 0;
                (value & C) ? SetFlag(C) : ClearFlag(C);
                value = (value >> 1) | carry;
                Cycles--;
                mem.WriteByte(Cycles, addr, value);
                RegisterSetZNStatus(value);
            }
            return;
        }
        case Instruction::JMP:
        {
			Word jmp_addr;
            if (operation.mode == ABSOLUTE) {
                jmp_addr = mem.FetchWord(Cycles, PC);
            }
            else {
                Word indirect_addr = mem.FetchWord(Cycles, PC);
    			Word indirect_high = indirect_addr & 0xFF00;
	    		Byte indirect_low = indirect_addr & 0x00FF;
    			Word low_byte = mem.ReadByte(Cycles, indirect_high | indirect_low);
                indirect_low++;
                Word high_byte = mem.ReadByte(Cycles, indirect_high | indirect_low) << 8;
	    		jmp_addr = high_byte | low_byte;
            }
            PC = jmp_addr;
            return;
        }
        case Instruction::JSR:
        {
            Word jmp_addr = FetchAddress(operation);
            mem[0x0100 | S--] = ((PC - 1) >> 8) & 0xFF;
            mem[0x0100 | S--] = (PC - 1) & 0xFF;
            PC = jmp_addr;
            Cycles -= 3;
            return;
        }
        case Instruction::RTS:
        {
            Word newPC = mem[0x0100 | ++S];
            mem[0x0100 | S] = 0xFF;
            newPC |= (mem[0x0100 | ++S] << 8);
            mem[0x0100 | S] = 0xFF;
            PC = newPC + 1;
			Cycles -= 5;
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
            Cycles--;
            return;
        case Instruction::CLD:
            ClearFlag(D);
            Cycles--;
            return;
        case Instruction::CLI:
            ClearFlag(I);
            Cycles--;
            return;
        case Instruction::CLV:
            ClearFlag(V);
            Cycles--;
            return;
        case Instruction::SEC:
            SetFlag(C);
            Cycles--;
            return;
        case Instruction::SED:
            SetFlag(D);
            Cycles--;
            return;
        case Instruction::SEI:
            SetFlag(I);
            Cycles--;
            return;
        case Instruction::BRK:
			(void) mem.FetchByte(Cycles, PC);
			mem[0x0100 | S--] = (PC >> 8) & 0xFF;
			mem[0x0100 | S--] = PC & 0xFF;
            SetFlag(B);
            mem[0x0100 | S--] = P;
			Cycles -= 3;
            PC = mem.ReadWord(Cycles, 0xFFFE);
            return;
        case Instruction::NOP:
            Cycles--;
            return;
        case Instruction::RTI:
        {
            P = mem[0x0100 | ++S];
            mem[0x0100 | S] = 0xFF;
            ClearFlag(B);
            Word newPC = mem[0x0100 | ++S];
            mem[0x0100 | S] = 0xFF;
            newPC |= (mem[0x0100 | ++S] << 8);
            mem[0x0100 | S] = 0xFF;
            PC = newPC;
            Cycles -= 5;
            return;
        }
        }

    }

    // Run the emulator
    //    Runs the emulator for a requested number of cycles, or indefinitely if chosen. The function
    //    may return early in the case of an error in execution. The function may also return late if
    //    an instruction requires more cycles than are left.
    // 
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