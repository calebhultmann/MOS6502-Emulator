#include <stdint.h>

#include "MOS6502.h"

class Memory
{
public:
	Memory();
	~Memory();

	void ReadByte();
	MOS6502 cpu;

private:
	// 64KB memory
	static constexpr uint32_t MAX_MEM = 1024 * 64;
	uint8_t Data[MAX_MEM];
	

};