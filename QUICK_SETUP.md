# Quick Setup Guide for Windows

## Option 1: Using MSYS2 (Recommended)

1. **Download and Install MSYS2:**
   - Go to https://www.msys2.org/
   - Download and run the installer
   - Follow the installation wizard

2. **Open MSYS2 Terminal and install tools:**
   ```bash
   pacman -Syu
   pacman -S mingw-w64-x86_64-gcc
   pacman -S nasm
   pacman -S make
   pacman -S mingw-w64-x86_64-qemu
   ```

3. **Build CyberOS:**
   ```bash
   cd /d/cybersecurity101
   make all
   make run
   ```

## Option 2: Using WSL (Windows Subsystem for Linux)

1. **Install WSL:**
   ```powershell
   wsl --install
   ```

2. **Install Ubuntu tools:**
   ```bash
   sudo apt update
   sudo apt install build-essential nasm qemu-system-x86 gcc-multilib
   ```

3. **Build and run:**
   ```bash
   cd /mnt/d/cybersecurity101
   make all
   make run
   ```

## Option 3: Docker (Easiest)

Create a Docker environment with all tools pre-installed:

```dockerfile
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y \
    build-essential nasm qemu-system-x86 gcc-multilib
WORKDIR /cyberos
```

## What You'll See When Running:

1. **QEMU window opens** showing a virtual computer
2. **Boot sequence** displays bootloader messages
3. **CyberOS starts** with the welcome screen
4. **Interactive shell** where you can type commands
5. **Real keyboard input** with immediate response

The actual OS will look exactly like the preview, but running on real (virtual) hardware!
