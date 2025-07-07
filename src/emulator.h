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

    // Copy/import from an external Memory object into the CPUs internal memory
    void ImportCode(Mem& extMem)
    {
        for (u32 i = 0; i < mem.MAX_MEM; i++)
        {
            mem.Data[i] = extMem.Data[i];
        }
    }

    // Execute the current instruction
    void ExecuteOperation(Operation operation) {
        Instruction instruction = operation.instruction;
        switch (instruction) {
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
        case Instruction::BRK:
			(void) mem.FetchByte(Cycles, PC);
			mem[0x0100 | S--] = (PC >> 8) & 0xFF;
			mem[0x0100 | S--] = PC & 0xFF;
            SetFlag(B);
            mem[0x0100 | S--] = P;
			Cycles -= 3;
            PC = mem.ReadWord(Cycles, 0xFFFE);
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