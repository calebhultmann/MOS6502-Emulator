#include "emulator.h"
#include "instructions.h"
#include "mappings.h"
#include <stdexcept>
#include <iostream>
struct Mem
{
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
};

struct CPU
{
    Word PC; // Program Counter
    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y
    Byte S;  // Stack Pointer
    Byte P;  // Processor Status

    Byte C : 1; // Carry Flag
    Byte Z : 1; // Zero Flag
    Byte I : 1; // Interrupt Disable Flag
    Byte D : 1; // Decimal Mode Flag
    Byte B : 1; // Break Command Flag
    Byte V : 1; // Overflow Flag
    Byte N : 1; // Negative Flag

    u32 Cycles;
    Mem mem;

    // Set the Z and N flags with respect to a register; Very common result of many opcodes
    void RegisterSetZNStatus(Byte Data)
    {
        Z = (Data == 0);
        N = (Data & 0b10000000) > 0;
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
        Word startAdd = (mem[0xFFFC] | (mem[0xFFFD] << 8));
        PC = mem[startAdd];
        SP = 0xFF;
        C = Z = I = D = B = V = N = 0;
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
        case IMMEDIATE:
            return mem.FetchByte(Cycles, PC);
        case ABSOLUTE:
            // THIS ISN'T RIGHT
            return mem.FetchWord(Cycles, PC);
        case X_ABSOLUTE:
            return mem.FetchByte(Cycles, PC) + X;
        case Y_ABSOLUTE:
            return mem.FetchByte(Cycles, PC) + Y;
        case ABS_INDIRECT:
        {
            Word address = mem.FetchWord(Cycles, PC);
            return;
            //return mem.ReadWord(Cycles, address);
        }
        case ZERO_PAGE:
            Byte ZPByte = mem.FetchByte(Cycles, PC);
            return;
        }
        
    }

    std::pair<int, int> FetchDataWithAddress(Operation operation) {
        AddressMode mode = operation.mode;
        switch (mode) {

        }
    }

	// Execute the current instruction
    void ExecuteInstruction(Operation operation) {
		// do jump and jsr first as they require a word from memory not a byte
        // have to do every instruction that involves writing back to memory, not currently implemented
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
        case "STA": // NOT DONE
        case "STX": // NOT DONE
        case "STY": // NOT DONE
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
        case "PHA": // NOT DONE
        case "PHP": // NOT DONE
        case "PLA": // NOT DONE
        case "PLP": // NOT DONE
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
        case "SBC": // NOT DONE
        case "CMP": // NOT DONE
        case "CPX": // NOT DONE
        case "CPY": // NOT DONE
        case "INC": // NOT DONE
        case "INX":
            X++;
            RegisterSetZNStatus(X);
            return;
        case "INY":
            Y++;
            RegisterSetZNStatus(Y);
            return;
        case "DEC": // NOT DONE
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
            C = 0;
            return;
        case "CLD":
            D = 0;
            return;
        case "CLI":
            I = 0;
            return;
        case "CLV":
            V = 0;
            return;
        case "SEC":
            C = 1;
            return;
        case "SED":
            D = 1;
            return;
        case "SEI":
            I = 1;
            return;
        case "BRK": // NOT DONE
        case "NOP":
            PC++;
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
            // DEC - Decrement Memory
            case INS_DEC_ZP:
            {
                Byte ZPByte = mem.FetchByte(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZPByte));
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZPByte), Value - 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            case INS_DEC_ZPX:
            {
                Byte ZPByte = mem.FetchByte(Cycles, PC);
                ZPByte += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZPByte));
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZPByte), Value - 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            case INS_DEC_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                mem.WriteByte(Cycles, AbsAddress, Value - 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            case INS_DEC_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                AbsAddress += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                mem.WriteByte(Cycles, AbsAddress, Value - 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            // INC - Increment Memory
            case INS_INC_ZP:
            {
                Byte ZPByte = mem.FetchByte(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZPByte));
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZPByte), Value + 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            case INS_INC_ZPX:
            {
                Byte ZPByte = mem.FetchByte(Cycles, PC);
                ZPByte += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZPByte));
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZPByte), Value + 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            case INS_INC_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                mem.WriteByte(Cycles, AbsAddress, Value + 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
            } break;
            case INS_INC_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                AbsAddress += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                mem.WriteByte(Cycles, AbsAddress, Value + 1);
                Z = (Value == 0);
                N = (Value & 0b10000000) > 0;
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
            // ROR - Rotate Right

            // STA - Store Accumulator
            case INS_STA_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte), A);
            } break;
            case INS_STA_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte), A);
            } break;
            case INS_STA_ABS:
            {
                Word Address = mem.FetchWord(Cycles, PC);
                mem.WriteByte(Cycles, Address, A);
            } break;
            case INS_STA_ABSX:
            {
                Word Address = mem.FetchWord(Cycles, PC);
                Address += X;
                Cycles--;
                mem.WriteByte(Cycles, Address, A);
            } break;
            case INS_STA_ABSY:
            {
                Word Address = mem.FetchWord(Cycles, PC);
                Address += Y;
                Cycles--;
                mem.WriteByte(Cycles, Address, A);
            } break;

            // STX - Store X Register
            case INS_STX_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte), X);
            } break;
            case INS_STX_ZPY:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += Y;
                Cycles--;
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte), X);
            } break;
            case INS_STX_ABS:
            {
                Word Address = mem.FetchWord(Cycles, PC);
                mem.WriteByte(Cycles, Address, X);
            } break;

            // STY - Store Y Register
            case INS_STY_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte), Y);
            } break;
            case INS_STY_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                mem.WriteByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte), Y);
            } break;
            case INS_STY_ABS:
            {
                Word Address = mem.FetchWord(Cycles, PC);
                mem.WriteByte(Cycles, Address, Y);
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