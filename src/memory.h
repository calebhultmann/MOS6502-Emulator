using SByte = int8_t;
using Byte = uint8_t;
using Word = uint16_t;
using u32 = uint32_t;

struct Mem
{
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