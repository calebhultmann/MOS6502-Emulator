add_library(emulator
			bus.cpp bus.h
			instructions.h
			mappings.h
			opcodes.h
			MOS6502.cpp MOS6502.h)

add_library(test_include_reqs
			bus.cpp bus.h
			MOS6502.cpp MOS6502.h
			opcodes.h)
target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test_include_reqs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})