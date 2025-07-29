# CyberOS Advanced v2.0 - A Feature-Rich Operating System

This is an advanced x86 operating system written from scratch for cybersecurity education and OS development learning.

## 🚀 NEW FEATURES v2.0

### 🧮 **Advanced Calculator**
- Mathematical expression evaluation
- Support for +, -, *, /, % operators
- Parentheses support for complex expressions
- Example: `calc (15 + 27) * 2 / 3`

### 🎮 **Built-in Games & Entertainment**
- Snake game with WASD controls
- Number guessing game
- Interactive ASCII art displays
- Matrix digital rain effect

### 🎨 **Dynamic Themes & Visual Effects**
- Multiple color themes (Green, Blue, Red)
- Rainbow text mode with color cycling
- Professional ASCII art logo
- Enhanced visual feedback

### 💾 **Memory Management System**
- Dynamic memory allocation (kmalloc/kfree)
- Real-time memory statistics
- Heap management with block merging
- Memory usage monitoring

### ⏰ **Timer & System Monitoring**
- System uptime tracking
- Programmable Interval Timer (PIT)
- Performance monitoring
- Delay functions for animations

### 🔧 **Enhanced Shell Interface**
- Professional help system with ASCII tables
- Improved error handling and feedback
- Command categorization
- Enhanced user experience

## Core Features

- **Custom Bootloader** - 16-bit to 32-bit protected mode transition
- **Kernel Architecture** - Modular design with proper abstraction layers
- **VGA Text Driver** - 80x25 color display with advanced graphics
- **Interrupt System** - IDT setup and hardware interrupt foundation
- **PS/2 Keyboard** - Real-time input with scancode translation
- **Hardware Abstraction** - Port I/O wrapper functions

## Available Commands

### 🖥️ **System Commands**
- `help` - Display comprehensive command help
- `clear` - Clear screen and reset cursor
- `info` - Show detailed system information
- `halt` - Graceful system shutdown
- `uptime` - Display system uptime
- `memory` - Show memory usage statistics
- `date` - Display current session info

### 🧮 **Calculator & Utilities**
- `calc [expression]` - Evaluate mathematical expressions
- `calc` - Show calculator help and examples

### 🎮 **Games & Entertainment**
- `snake` - Play the classic Snake game
- `guess` - Number guessing game
- `logo` - Display CyberOS ASCII art logo
- `matrix` - Matrix digital rain effect

### 🎨 **Themes & Visual Effects**
- `theme [color]` - Change color scheme (green/blue/red)
- `theme` - List available themes
- `rainbow` - Display rainbow text effect

## Quick Start

```bash
# Build the OS
make clean && make all

# Run in emulator
make run

# Or use the enhanced build script
./build_and_run.bat run
```

## Example Usage

```
cyberos> calc (100 + 50) / 3
Result: 0x32

cyberos> memory
┌─────────────────────────────────────┐
│           MEMORY STATUS             │
├─────────────────────────────────────┤
│ Total Memory:  0x100000 bytes       │
│ Used Memory:   0x15420 bytes        │
│ Free Memory:   0xEABE0 bytes        │
│ Alloc Blocks:  0x7                  │
└─────────────────────────────────────┘

cyberos> theme blue
Theme changed to: Ocean Blue

cyberos> snake
[Snake game interface loads...]
```

## Structure

- `boot/` - Bootloader code
- `kernel/` - Kernel source code
- `include/` - Header files
- `build/` - Build output directory
- `scripts/` - Build and utility scripts

## Getting Started

1. Install the required tools (see docs/setup.md)
2. Build the project with `make`
3. Test in QEMU with `make run`

## Learning Resources

- [OSDev Wiki](https://wiki.osdev.org/)
- [Writing a Simple Operating System from Scratch](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
