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
	Word ReadWord(u32& Cycles, Word Address);
	Byte FetchByte(u32& Cycles, Word& PC);
	Word FetchWord(u32& Cycles, Word& PC);
	void WriteByte(u32& Cycles, Word Address, Byte Value);
	void WriteWord(u32& Cycles, Word Address, Word Value);
	void PushStack(Byte& SP, Byte Value);
	Byte PullStack(Byte& SP);
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

	void SetFlag(Byte flag);
	void ClearFlag(Byte flag);

	void RegisterSetZNStatus(Byte Data);
	Word ZPByteToAddress(u32& Cycles, Byte ZPByte);
	
	void Reset();

	Operation FetchOperation();
	Byte FetchData(Operation operation);
	Word FetchAddress(Operation operation);
	void ExecuteInstruction(Operation operation);
	void Run(u32 Cycles);
};