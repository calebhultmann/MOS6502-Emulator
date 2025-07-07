add_library(emulator bimap.cpp bimap.h instructions.h mappings.h bus.cpp bus.h MOS6502.cpp MOS6502.h)
target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})