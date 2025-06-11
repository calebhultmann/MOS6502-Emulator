#include "emulator.h"
#include "instructions.h"

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

    // Word ReadWord(u32 &Cycles, Word Address) ?

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
    // Set the Z and N flags with respect to a register; Very common result of many opcodes
    void RegisterSetZNStatus(Byte& Register)
    {
        Z = (Register == 0);
        N = (Register & 0b10000000) > 0;
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

    // Execute instructions
    void Execute(u32 Cycles)
    {
        while (Cycles > 0)
        {
            Byte Instruction = mem.FetchByte(Cycles, PC);
            switch (Instruction)
            {
                // AND - Logical AND
            case INS_AND_IM:
            {
                A = A & mem.FetchByte(Cycles, PC);
                RegisterSetZNStatus(A);
            } break;
            case INS_AND_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                A = A & mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(A);
            } break;
            case INS_AND_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                A = A & mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(A);
            } break;
            case INS_AND_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                A = A & mem.ReadByte(Cycles, AbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_AND_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + X;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = A & mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_AND_ABSY:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + Y;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = A & mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
            } break;

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

            // CLC - Clear Carry Flag
            case INS_CLC:
            {
                C = 0;
                Cycles--;
            } break;

            // CLD - Clear Decimal Mode
            case INS_CLD:
            {
                D = 0;
                Cycles--;
            } break;

            // CLI - Clear Interrupt Disable
            case INS_CLI:
            {
                I = 0;
                Cycles--;
            } break;

            // CLV - Clear Overflow Flag
            case INS_CLV:
            {
                V = 0;
                Cycles--;
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
            // DEX - Decrement X Register
            case INS_DEX:
            {
                X--;
                Cycles--;
                RegisterSetZNStatus(X);
            } break;

            // DEY - Decrement Y Register
            case INS_DEY:
            {
                Y--;
                Cycles--;
                RegisterSetZNStatus(Y);
            } break;

            // EOR - Exclusive OR
            case INS_EOR_IM:
            {
                A = A ^ mem.FetchByte(Cycles, PC);
                RegisterSetZNStatus(A);
            } break;
            case INS_EOR_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                A = A ^ mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(A);
            } break;
            case INS_EOR_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                A = A ^ mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(A);
            } break;
            case INS_EOR_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                A = A ^ mem.ReadByte(Cycles, AbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_EOR_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + X;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = A ^ mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_EOR_ABSY:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + Y;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = A ^ mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
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
            // INX - Increment X Register
            case INS_INX:
            {
                X++;
                Cycles--;
                RegisterSetZNStatus(X);
            } break;

            // INY - Increment Y Register
            case INS_INY:
            {
                Y++;
                Cycles--;
                RegisterSetZNStatus(Y);
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

            // LDA - Load Accumulator
            case INS_LDA_IM:
            {
                A = mem.FetchByte(Cycles, PC);
                RegisterSetZNStatus(A);
            } break;
            case INS_LDA_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                A = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(A);
            } break;
            case INS_LDA_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                A = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(A);
            } break;
            case INS_LDA_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                A = mem.ReadByte(Cycles, AbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_LDA_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + X;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_LDA_ABSY:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + Y;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
            } break;

            // LDX - Load X Register
            case INS_LDX_IM:
            {
                X = mem.FetchByte(Cycles, PC);
                RegisterSetZNStatus(X);
            } break;
            case INS_LDX_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                X = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(X);
            } break;
            case INS_LDX_ZPY:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += Y;
                Cycles--;
                X = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(X);
            } break;
            case INS_LDX_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                X = mem.ReadByte(Cycles, AbsAddress);
                RegisterSetZNStatus(X);
            } break;
            case INS_LDX_ABSY:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + Y;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                X = mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(X);
            } break;

            // LDY - Load Y Register
            case INS_LDY_IM:
            {
                Y = mem.FetchByte(Cycles, PC);
                RegisterSetZNStatus(Y);
            } break;
            case INS_LDY_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                Y = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(Y);
            } break;
            case INS_LDY_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                Y = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                RegisterSetZNStatus(Y);
            } break;
            case INS_LDY_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Y = mem.ReadByte(Cycles, AbsAddress);
                RegisterSetZNStatus(Y);
            } break;
            case INS_LDY_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + X;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                Y = mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(Y);
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

            // NOP - No Operation
            case INS_NOP:
            {
                PC++;
                Cycles--;
            } break;

            // ORA - Logical Inclusive OR
            case INS_ORA_IM:
            {
                Byte Value = mem.FetchByte(Cycles, PC);
                A = A | Value;
                RegisterSetZNStatus(A);
            } break;
            case INS_ORA_ZP:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                A = A | Value;
                RegisterSetZNStatus(A);
            } break;
            case INS_ORA_ZPX:
            {
                Byte ZeroPageByte = mem.FetchByte(Cycles, PC);
                ZeroPageByte += X;
                Cycles--;
                Byte Value = mem.ReadByte(Cycles, ZPByteToAddress(Cycles, ZeroPageByte));
                A = A | Value;
                RegisterSetZNStatus(A);
            } break;
            case INS_ORA_ABS:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Byte Value = mem.ReadByte(Cycles, AbsAddress);
                A = A | Value;
                RegisterSetZNStatus(A);
            } break;
            case INS_ORA_ABSX:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + X;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = A | mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
            } break;
            case INS_ORA_ABSY:
            {
                Word AbsAddress = mem.FetchWord(Cycles, PC);
                Word NewAbsAddress = AbsAddress + Y;
                if (AbsAddress >> 8 != NewAbsAddress >> 8)
                {
                    Cycles--;
                }
                A = A | mem.ReadByte(Cycles, NewAbsAddress);
                RegisterSetZNStatus(A);
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

            // SEC - Set Carry Flag
            case INS_SEC:
            {
                C = 1;
                Cycles--;
            } break;

            // SED - Set Decimal Flag
            case INS_SED:
            {
                D = 1;
                Cycles--;
            } break;

            // SEI - Set Interrupt Disable 
            case INS_SEI:
            {
                I = 1;
                Cycles--;
            } break;

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

            // TAX - Transfer Accumulator to X
            case INS_TAX:
            {
                X = A;
                Cycles--;
                RegisterSetZNStatus(X);
            } break;

            // TAY - Transfer Accumulator to Y
            case INS_TAY:
            {
                Y = A;
                Cycles--;
                RegisterSetZNStatus(Y);
            } break;

            // TXA - Transfer X to Accumulator
            case INS_TXA:
            {
                A = X;
                Cycles--;
                RegisterSetZNStatus(A);
            } break;

            // TYA - Transfer Y to Accumulator
            case INS_TYA:
            {
                A = Y;
                Cycles--;
                RegisterSetZNStatus(A);
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