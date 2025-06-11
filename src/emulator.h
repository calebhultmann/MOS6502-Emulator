using SByte = int8_t;
using Byte = uint8_t;
using Word = uint16_t;
using u32 = uint32_t;


struct Mem
{
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];

	void initialize();

	Byte ReadByte(u32& Cycles, Word addr);
	Byte FetchByte(u32& Cycles, Word &PC);
	Word FetchWord(u32& Cycles, Word& PC);
	void WriteByte(u32& Cycles, Word Address, Byte Value);
	void WriteWord(u32& Cycles, Word Address, Word Value);
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


	void RegisterSetZNStatus(Byte& reg);
	Word ZPByteToAddress(u32& Cycles, Byte ZPByte);
	
	void Reset();
	void Execute(u32 Cycles);
};