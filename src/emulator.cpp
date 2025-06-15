#include "emulator.h"
#include "instructions.h"
#include "mappings.h"
#include <stdexcept>
#include <iostream>

using SByte = int8_t;
using Byte = uint8_t;
using Word = uint16_t;
using u32 = uint32_t;

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
            Data[i] = 0;
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

    Byte ReadByte(u32& Cycles, Word Address)
    {
        Byte Value = Data[Address];
        Cycles--;
        return Value;
    }

    Word ReadWord(u32& Cycles, Word Address)
    {
        Word Value = Data[Address];
        Address++;
        Value |= (Data[Address] << 8);
        Cycles -= 2;
        return Value;
    }

    Byte FetchByte(u32& Cycles, Word& PC)
    {
        Byte Value = Data[PC];
        PC++;
        Cycles--;
        return Value;
    }

    Word FetchWord(u32& Cycles, Word& PC)
    {
        Word Value = Data[PC];
        PC++;
        Value |= (Data[PC] << 8);
        PC++;
        Cycles -= 2;
        return Value;
    }

    void WriteByte(u32& Cycles, Word Address, Byte Value)
    {
        Data[Address] = Value;
        Cycles--;
    }

    void WriteWord(u32& Cycles, Word Address, Word Value)
    {
        Data[Address] = Value & 0xFF;
        Data[Address + 1] = (Value >> 8) & 0xFF;
        Cycles -= 2;
    }

    void PushStack(Byte& SP, Byte Value)
    {
        Data[SP--] = Value;
    }

    Byte PullStack(Byte& SP)
    {
        Byte Value = Data[++SP];
        Data[SP] = 0x00;
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

    u32 Cycles;
    Mem mem;

    void SetFlag(Byte flag) {
        P |= flag;
    }

    void ClearFlag(Byte flag) {
        P &= ~flag;
    }

    // Set the Z and N flags with respect to a register; Very common result of many opcodes
    void RegisterSetZNStatus(Byte Data)
    {
        P = (P & ~Z) | ((Data == 0) * Z);
        P = (P & ~N) | (Data & N);
    }

    // Turn a zero-page byte into a workable 16-bit address
    Word ZPByteToAddress(u32& Cycles, Byte ZPByte)
    {
        Cycles--;
        return (0x0000 | ZPByte);
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

	// Fetch the next operation from memory
    Operation FetchOperation() {
        Byte Opcode = mem.FetchByte(Cycles, PC);
        Operation instruction;
        try {
            instruction = instruction_opcode_bimap.right.at(Opcode);
        } catch (std::out_of_range& e) {
			std::cout << "Unrecognized opcode: " << std::hex << (int)Opcode << std::dec << std::endl;
            instruction = { "Unknown", UNKNOWN };
        }
		return instruction;
    }

    // Fetch data for the current instruction based on address mode
    Byte FetchData(Operation operation) {
        // label, labelref, opcode, implied: not used

        AddressMode mode = operation.mode;
        switch (mode) {
        case ACCUMULATOR:
            return A;
        case RELATIVE:
            return mem.FetchByte(Cycles, PC); // NOT CORRECT
        case IMMEDIATE:
            return mem.FetchByte(Cycles, PC);
        case ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            return mem.ReadByte(Cycles, addr);
        }
        case ZERO_PAGE:
        {
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPByte);
            return mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZPByte));
        }
        case IMPLIED:
            return 0;
        case ABS_INDIRECT:
        {
            Word absolute_address = mem.FetchWord(Cycles, PC);
            Word indirect_address = mem.ReadWord(Cycles, absolute_address);
            return mem.ReadByte(Cycles, indirect_address);
        }
        case X_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            addr += X;
            return mem.ReadByte(Cycles, addr);
        }
        case Y_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            addr += Y;
            return mem.ReadByte(Cycles, addr);  
        }
        case X_ZERO_PAGE:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPBYte);
            ZPAddr += X;
            return mem.ReadByte(Cycles, ZPAddr);
        }
        case Y_ZERO_PAGE:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPBYte);
            ZPAddr += Y;
            return mem.ReadByte(Cycles, ZPAddr);
        }
        case X_INDEX_ZP_INDIRECT:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPBYte);
            ZPAddr += X;
            Word indirect_addr = mem.ReadWord(Cycles, ZPAddr);
            return mem.ReadByte(Cycles, indirect_addr);
        }
        case ZP_INDIRECT_Y_INDEX:
        {
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPByte);
            Word indirect_addr = mem.ReadWord(Cycles, ZPAddr);
            indirect_addr += Y;
            return mem.ReadByte(Cycles, indirect_addr);
        }
        }
        
    }

    // Acquires the effective address of the current instruction. Useful for instructions that write to memory
    Word FetchAddress(Operation operation) {
        AddressMode mode = operation.mode;
        switch (mode) {
        case ACCUMULATOR:
            return 0;
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
            return ZPByteToAddress(Cycles, ZPByte);
        }
        case IMPLIED:
            return 0;
        case ABS_INDIRECT:
        {
            Word absolute_address = mem.FetchWord(Cycles, PC);
            return mem.ReadWord(Cycles, absolute_address);
        }
        case X_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            return addr += X;
        }
        case Y_ABSOLUTE:
        {
            Word addr = mem.FetchWord(Cycles, PC);
            return addr += Y;
        }
        case X_ZERO_PAGE:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPBYte);
            return ZPAddr += X;
        }
        case Y_ZERO_PAGE:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPBYte);
            return ZPAddr += Y;
        }
        case X_INDEX_ZP_INDIRECT:
        {
            Byte ZPBYte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPBYte);
            ZPAddr += X;
            return mem.ReadWord(Cycles, ZPAddr);
        }
        case ZP_INDIRECT_Y_INDEX:
        {
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            Word ZPAddr = ZPByteToAddress(Cycles, ZPByte);
            Word indirect_addr = mem.ReadWord(Cycles, ZPAddr);
            return indirect_addr += Y;
        }
        }
    }

	// Execute the current instruction
    void ExecuteInstruction(Operation operation) {
		// do jump and jsr first as they require a word from memory not a byte
        // operations that don't use FetchData() must manually modify PC accordingly

        string instruction = operation.first;
        switch (instruction) {
        case "Unknown":
            return;
        case "LDA":
            A = FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case "LDX":
            X = FetchData(operation);
            RegisterSetZNStatus(X);
            return;
        case "LDY":
            Y = FetchData(operation);
            RegisterSetZNStatus(Y);
            return;
        case "STA": 
            Word addr = FetchAddress(operation);
            mem.WriteByte(Cycles, addr, A);
        case "STX":
            Word addr = FetchAddress(operation);
            mem.WriteByte(Cycles, addr, X);
        case "STY":
            Word addr = FetchAddress(operation);
            mem.WriteByte(Cycles, addr, Y);
        case "TAX":
            X = A;
            RegisterSetZNStatus(X);
            return;
        case "TAY":
            Y = A;
            RegisterSetZNStatus(Y);
            return;
        case "TXA":
            A = X;
            RegisterSetZNStatus(A);
            return;
        case "TYA":
            A = Y;
            RegisterSetZNStatus(A);
            return;
        case "TSX":
            X = S;
            RegisterSetZNStatus(X);
            return;
        case "TXS":
            S = X;
            return;
        case "PHA":
            mem.PushStack(S, A);
            return;
        case "PHP":
            mem.PushStack(S, P);
            return;
        case "PLA":
            A = mem.PullStack(S);
            RegisterSetZNStatus(A);
            return;
        case "PLP":
            P = mem.PullStack(S);
            return;
        case "AND":
            A = A & FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case "EOR":
            A = A ^ FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case "ORA":
            A = A | FetchData(operation);
            RegisterSetZNStatus(A);
            return;
        case "BIT":
        {
            Byte result = A & FetchData(operation);
            RegisterSetZNStatus(result);
            V = (result & 0b01000000) > 0;
            return;
        }
        case "ADC": // NOT DONE
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
        case "SBC": // NOT DONE
        case "CMP": // NOT DONE
        case "CPX": // NOT DONE
        case "CPY": // NOT DONE
        case "INC": // NOT DONE
            Word addr = FetchAddress(operation);
            RegisterSetZNStatus(++mem[addr]);
            return;
        case "INX":
            X++;
            RegisterSetZNStatus(X);
            return;
        case "INY":
            Y++;
            RegisterSetZNStatus(Y);
            return;
        case "DEC":
            Word addr = FetchAddress(operation);
            RegisterSetZNStatus(--mem[addr]);
            return;
        case "DEX":
            X--;
            RegisterSetZNStatus(X);
            return;
        case "DEY":
            Y--;
            RegisterSetZNStatus(X);
            return;
        case "ASL": // NOT DONE
            
            if (operation.mode != ACCUMULATOR) {

            }
        case "LSR": // NOT DONE
        case "ROL": // NOT DONE
        case "ROR": // NOT DONE
        case "JMP": // NOT DONE
        case "JSR": // NOT DONE
        case "RTS": // NOT DONE
        case "BCC": // NOT DONE
        case "BCS": // NOT DONE
        case "BEQ": // NOT DONE
        case "BMI": // NOT DONE
        case "BNE": // NOT DONE
        case "BPL": // NOT DONE
        case "BVC": // NOT DONE
        case "BVS": // NOT DONE
        case "CLC":
            ClearFlag(C);
            return;
        case "CLD":
            ClearFlag(D);
            return;
        case "CLI":
            ClearFlag(I);
            return;
        case "CLV":
            ClearFlag(V);
            return;
        case "SEC":
            SetFlag(C);
            return;
        case "SED":
            SetFlag(D);
            return;
        case "SEI":
            SetFlag(I);
            return;
        case "BRK": // NOT DONE
        case "NOP":
            return;
        case "RTI": // NOT DONE


        }

    }

    // Run the emulator
    void Run(u32 Cycles)
    {
        while (Cycles > 0)
        {

            switch (Instruction)
            {
            // ASL - Arithmetic Shift Left
            case INS_ASL_ACC:
            {
                C = A & 0x10000000;
                A = A << 1;
                Cycles--;
                RegisterSetZNStatus(A);
            } break;
            case INS_ASL_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                C = Value & 0x10000000;
                Value = Value << 1;
                Cycles--;
                mem.WriteByte(Cycles, ZeroPageByte, Value);
            } break;
            case INS_ASL_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                C = Value & 0x10000000;
                Value = Value << 1;
                Cycles--;
                mem.WriteByte(Cycles, ZeroPageByte, Value);
            } break;
            case INS_ASL_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                C = Value & 0x10000000;
                Value = Value << 1;
                Cycles--;
                mem.WriteByte(Cycles, AbsAddress, Value);
            } break;
            case INS_ASL_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                AbsAddress += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                C = Value & 0x10000000;
                Value = Value << 1;
                Cycles--;
                mem.WriteByte(Cycles, AbsAddress, Value);
            } break;

            // BCC - Branch if Carry Clear
            case INS_BCC:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (!C)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BCS - Branch if Carry Set
            case INS_BCS:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (C)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BEQ - Branch if Equal
            case INS_BEQ:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (Z)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BIT - Bit Test
            case INS_BIT_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));

                Z = (A & Value == 0);
                V = (Value & 0b01000000 == 0b01000000);
                N = (Value & 0b10000000 == 0b10000000);
            } break;
            case INS_BIT_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, AbsAddress);

                Z = (A & Value == 0);
                V = (Value & 0b01000000 == 0b01000000);
                N = (Value & 0b10000000 == 0b10000000);
            } break;

            // BMI - Branch if Minus
            case INS_BMI:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (N)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BNE - Branch if Not Equal
            case INS_BNE:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (!Z)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BPL - Branch if Positive
            case INS_BPL:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (!N)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BVC - Branch if Overflow Clear
            case INS_BVC:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (!V)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;

            // BVS - Branch if Overflow Set
            case INS_BVS:
            {
                Byte offset = mem.FetchByte(Cycles, PC);

                if (V)
                {
                    const Word oldPC = PC;
                    PC += static_cast<SByte>(offset);
                    Cycles--;

                    const bool PageCross = (PC >> 8) != (oldPC >> 8);
                    if (PageCross)
                    {
                        Cycles--;
                    }
                }
            } break;
            // JSR - Jump to Subroutine
            case INS_JSR_ABS:
            {
                Word SubRoutineAddress = mem.FetchWord(Cycles, PC);
                mem.WriteWord(Cycles, 0x0100 + SP, PC - 1);
                SP -= 2;
                PC = SubRoutineAddress;
                Cycles--;
            } break;

            // LSR - Logical Shift Right
            case INS_LSR_ACC:
            {
                C = A & 1;
                A = A >> 1;
                Cycles--;
                RegisterSetZNStatus(A);
            } break;
            case INS_LSR_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                C = Value & 1;
                Value = Value >> 1;
                Cycles--;
                mem.WriteByte(Cycles, ZeroPageByte, Value);
                Z = (Value == 0);
                N = (Value & 0b10000000);
            } break;
            case INS_LSR_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                C = Value & 1;
                Value = Value >> 1;
                Cycles--;
                mem.WriteByte(Cycles, ZeroPageByte, Value);
                Z = (Value == 0);
                N = (Value & 0b10000000);
            } break;
            case INS_LSR_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                C = Value & 1;
                Value = Value >> 1;
                Cycles--;
                mem.WriteByte(Cycles, AbsAddress, Value);
                Z = (Value == 0);
                N = (Value & 0b10000000);
            } break;
            case INS_LSR_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                AbsAddress += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                C = Value & 1;
                Value = Value >> 1;
                Cycles--;
                mem.WriteByte(Cycles, AbsAddress, Value);
                Z = (Value == 0);
                N = (Value & 0b10000000);
            } break;
            // ROL - Rotate Left
            case INS_ROL_ACC:
            {

            } break;
            case INS_ROL_ZP:
            {

            } break;
            case INS_ROL_ZPX:
            {

            } break;
            case INS_ROL_ABS:
            {

            } break;
            case INS_ROL_ABSX:
            {

            } break;

            // Unresolved opcode
            default:
            {
                printf("Instruction not handled %d\n", Instruction);
            } break;
            }
        }
    }

};