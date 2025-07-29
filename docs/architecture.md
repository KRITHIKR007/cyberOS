# CyberOS Architecture

## Overview

CyberOS is a simple x86 operating system designed for educational purposes. It demonstrates the fundamental concepts of OS development including:

- Bootloading
- Protected mode switching
- Memory management basics
- Interrupt handling
- Hardware abstraction
- Basic I/O operations

## Boot Process

1. **BIOS Stage**: BIOS loads the bootloader from the first sector (512 bytes) of the disk
2. **Bootloader Stage**: The bootloader (`boot/boot.asm`) switches to protected mode and loads the kernel
3. **Kernel Entry**: The kernel starts execution from `kernel/entry.asm`
4. **Kernel Main**: Control passes to `kernel_main()` in `kernel/kernel.c`

## Memory Layout

```
0x00000000 - 0x000003FF : Real Mode Interrupt Vector Table
0x00000400 - 0x000004FF : BIOS Data Area
0x00000500 - 0x00007BFF : Free memory (bootloader stack)
0x00007C00 - 0x00007DFF : Bootloader (512 bytes)
0x00007E00 - 0x0009FFFF : Free memory
0x000A0000 - 0x000BFFFF : Video memory
0x000C0000 - 0x000FFFFF : BIOS ROM
0x00100000 - ...        : Kernel and free memory
```

## Components

### Bootloader
- **File**: `boot/boot.asm`
- **Purpose**: Load kernel and switch to protected mode
- **Size**: 512 bytes (single sector)

### Kernel
- **Entry Point**: `kernel/entry.asm`
- **Main Code**: `kernel/kernel.c`
- **Libraries**: VGA display, keyboard input, string operations

### Drivers
- **VGA Driver**: Text mode display (80x25 characters)
- **Keyboard Driver**: Basic PS/2 keyboard input
- **Port I/O**: Hardware communication functions

## Key Features

1. **VGA Text Mode**: 80x25 character display with color support
2. **Basic Shell**: Command-line interface with built-in commands
3. **Interrupt Handling**: Foundation for hardware interrupts
4. **Memory Management**: Basic memory operations
5. **Hardware Abstraction**: Port I/O wrapper functions

## Future Enhancements

- File system support
- Process management
- Virtual memory
- Network stack
- GUI support
- Advanced device drivers
