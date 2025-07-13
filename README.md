# MOS6502 Emulator

A cycle-accurate emulator of the MOS6502 microprocessor, written in modern C++.  
Designed for correctness, testability, and extensibility.

---

## Overview

The **MOS6502-Emulator** is a complete, cycle-accurate emulation of the original MOS6502 chip.  
All legal opcodes are supported and executed with timing accuracy. The emulator is connected to a virtual 64KB RAM, replicating the memory map and behavior of real hardware.

---

## Features

- All **legal 6502 opcodes** implemented
- **Cycle-accurate** execution for each instruction
- **Unit tests** for every opcode utilizing Google Test
- **Virtual 64KB RAM** memory space
- Built in **modern C++** with support for `vcpkg` dependency management

---

## Installation

You can build the emulator using **CMake**. Make sure you have Boost installed via vcpkg (see Dependencies).

```bash
git clone https://github.com/your-username/MOS6502-Emulator.git
cd MOS6502-Emulator
mkdir build
cd build
cmake ..
cmake --build .
```
## Dependencies

- [CMake](https://cmake.org/)
- [GoogleTest](https://github.com/google/googletest)
- [Boost Bimap](https://www.boost.org/) (install via [vcpkg](https://vcpkg.io/))

> *Make sure Boost is installed and accessible via vcpkg:*

```bash
vcpkg install boost-bimap
```
---

## Testing

Unit tests are written with Google Test and cover all legal opcodes for correctness.

To run tests:

```bash
cd build
ctest
```
---

## Usage

Executable currently supports internal test functions.

A basic 6502 assembler is in progress to allow loading and running of custom programs.

Stay tuned for:
- `.asm` support
- Command-line interface
- Memory inspection tools

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Author

**Caleb Hultmann**

Upcoming projects include:
- NES Emulator using a modified version of this emulator
- Portfolio Website using Github Pages
---

## Screenshots & Demo

Coming soon!

---

## TODO

- [X] Separate CPU and Bus class implementations to allow for future component additions
- [X] Add exit status usage
- [ ] Reorganize files and code implementation
- [ ] Increase readability of code with comments
- [ ] Implement git submodule for vcpkg to remove the necessity for a local installation
- [ ] Complete in-progress 6502 assembler
- [ ] Implement rudimentary I/O for text or graphics to expand CPU capabilities
- [ ] Write test programs to feature functionalities