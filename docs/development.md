# CyberOS Development Guide

## Getting Started

Welcome to CyberOS development! This guide will help you understand and extend the operating system.

## Project Structure

```
cybersecurity101/
├── boot/               # Bootloader code
│   └── boot.asm       # Main bootloader
├── kernel/            # Kernel source code
│   ├── entry.asm      # Kernel entry point
│   ├── kernel.c       # Main kernel code
│   ├── vga.c          # VGA display driver
│   ├── keyboard.c     # Keyboard driver
│   ├── interrupts.c   # Interrupt handling
│   ├── ports.c        # Hardware port I/O
│   ├── string.c       # String operations
│   └── idt_flush.asm  # IDT loading assembly
├── include/           # Header files
│   ├── vga.h
│   ├── keyboard.h
│   ├── interrupts.h
│   ├── ports.h
│   └── string.h
├── docs/              # Documentation
├── build/             # Build output (created during build)
├── Makefile           # Build configuration
├── linker.ld          # Linker script
└── README.md          # Project overview
```

## Building and Running

### Prerequisites
- NASM assembler
- GCC cross-compiler (i686-elf-gcc preferred)
- GNU Make
- QEMU (for testing)

### Build Commands
```bash
make clean      # Clean build files
make all        # Build the OS
make run        # Build and run in QEMU
make help       # Show available targets
```

### Windows Users
Use the provided batch file:
```cmd
build_and_run.bat      # Build only
build_and_run.bat run  # Build and run
```

## Understanding the Code

### Boot Process
1. **BIOS loads bootloader** at 0x7C00
2. **Bootloader** switches to protected mode and loads kernel
3. **Kernel entry** sets up stack and calls kernel_main()
4. **Kernel main** initializes drivers and starts main loop

### Key Components

#### VGA Driver (`kernel/vga.c`)
- Manages 80x25 text mode display
- Provides color support
- Handles scrolling and cursor positioning

#### Keyboard Driver (`kernel/keyboard.c`)
- Reads PS/2 keyboard input
- Converts scancodes to ASCII
- Implements simple command processing

#### Interrupt System (`kernel/interrupts.c`)
- Sets up Interrupt Descriptor Table (IDT)
- Foundation for hardware interrupt handling

## Adding New Features

### Adding a New Command
1. Modify `process_command()` in `kernel/keyboard.c`
2. Add your command logic
3. Update help text

Example:
```c
else if (strcmp(cmd, "time") == 0) {
    vga_print("\\nCurrent time: Not implemented yet\\n");
}
```

### Adding a New Driver
1. Create new `.c` and `.h` files
2. Add to Makefile
3. Include in `kernel/kernel.c`
4. Initialize in `kernel_main()`

### Memory Management
The current OS has basic memory layout but no dynamic allocation. To add:
1. Implement heap management
2. Add malloc/free functions
3. Update linker script if needed

## Debugging Tips

### Common Issues
- **Build errors**: Check cross-compiler installation
- **Boot failure**: Verify bootloader signature (0xAA55)
- **Kernel panic**: Add debug prints to trace execution
- **QEMU issues**: Check QEMU installation and path

### Debugging Techniques
1. Add debug prints with `vga_print()`
2. Use QEMU monitor commands
3. Check memory layout with objdump
4. Verify assembly output with disassemblers

## Advanced Topics

### File System
To add file system support:
1. Choose a simple FS (FAT12/16)
2. Implement disk reading functions
3. Add file operations
4. Update bootloader to load from FS

### Multitasking
For basic multitasking:
1. Implement task switching
2. Add scheduler
3. Set up timer interrupts
4. Manage task states

### Networking
For network support:
1. Add Ethernet driver
2. Implement TCP/IP stack
3. Add socket interface
4. Test with simple protocols

## Resources

- [OSDev Wiki](https://wiki.osdev.org/) - Comprehensive OS development resource
- [Intel Architecture Manuals](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
- [NASM Documentation](https://www.nasm.us/docs.php)
- [GCC Cross-Compiler Guide](https://wiki.osdev.org/GCC_Cross-Compiler)

## Contributing

1. Fork the project
2. Create a feature branch
3. Test your changes thoroughly
4. Document new features
5. Submit a pull request

Happy OS development!
