add_library(emulator emulator.cpp emulator.h bimap.cpp bimap.h instructions.h mappings.h)
target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})