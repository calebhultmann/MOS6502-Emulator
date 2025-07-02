#include "ram.h"

Memory::Memory() {
	for (uint32_t i = 0; i < MAX_MEM; i++) {
		Data[i] = 0xFF;
	}
	Data[0xFFFC] = 0x00;
	Data[0xFFFD] = 0x02;
}

Memory::~Memory() {

}
