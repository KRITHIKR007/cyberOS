# Setting Up the Development Environment

## Required Tools

### Windows (using WSL or MSYS2)

1. **Install MSYS2**
   - Download from https://www.msys2.org/
   - Follow installation instructions

2. **Install required packages**
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S nasm
   pacman -S make
   pacman -S qemu
   ```

3. **Cross-compiler setup**
   You'll need a cross-compiler targeting i686-elf:
   ```bash
   # This is a simplified approach - you may need to build from source
   # or use a pre-built toolchain
   ```

### Linux

1. **Install packages**
   ```bash
   sudo apt-get install build-essential nasm qemu-system-x86
   
   # For cross-compiler
   sudo apt-get install gcc-multilib
   ```

2. **Build cross-compiler (if needed)**
   Follow the instructions at: https://wiki.osdev.org/GCC_Cross-Compiler

## Building the OS

1. **Clone/download the project**
2. **Build the project**
   ```bash
   make clean
   make all
   ```

3. **Run in QEMU**
   ```bash
   make run
   ```

## Troubleshooting

- If you get linking errors, make sure you have a proper cross-compiler
- If QEMU doesn't start, check that it's installed and in your PATH
- For Windows users, make sure you're using the correct shell environment

## Next Steps

1. Study the bootloader code in `boot/boot.asm`
2. Understand the kernel entry point in `kernel/entry.asm`
3. Explore the C kernel code in `kernel/kernel.c`
4. Try modifying the welcome message
5. Add new commands to the shell
