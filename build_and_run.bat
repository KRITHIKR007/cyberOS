@echo off
echo Building CyberOS...

REM Check if build tools are available
where nasm >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: NASM not found. Please install NASM assembler.
    echo Download from: https://www.nasm.us/pub/nasm/releasebuilds/
    exit /b 1
)

REM Try cross-compiler first, then regular gcc
where i686-elf-gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo Warning: i686-elf-gcc not found. Trying regular gcc...
    where gcc >nul 2>nul
    if %errorlevel% neq 0 (
        echo Error: No suitable C compiler found.
        echo Please install MinGW-w64 or MSYS2 with gcc
        exit /b 1
    )
    echo Using regular gcc with 32-bit flags
)

REM Check for make
where make >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: Make not found. Please install GNU Make.
    echo You can get it from MSYS2 or MinGW-w64
    exit /b 1
)

REM Create build directory
if not exist build mkdir build

REM Build the project
echo Cleaning previous build...
make clean 2>nul
echo Building OS image...
make all

if %errorlevel% eq 0 (
    echo.
    echo =======================================
    echo Build successful!
    echo =======================================
    echo.
    if "%1"=="run" (
        where qemu-system-i386 >nul 2>nul
        if %errorlevel% neq 0 (
            echo Warning: QEMU not found. Cannot run automatically.
            echo Please install QEMU to test the OS.
            echo Download from: https://www.qemu.org/download/
            echo.
            echo You can manually run: qemu-system-i386 -fda build\cyberos.img
        ) else (
            echo Starting CyberOS in QEMU...
            make run
        )
    ) else (
        echo To test the OS, run: build_and_run.bat run
        echo Or manually: qemu-system-i386 -fda build\cyberos.img
    )
) else (
    echo.
    echo =======================================
    echo Build failed!
    echo =======================================
    echo.
    echo Common solutions:
    echo 1. Install MSYS2 and required packages
    echo 2. Make sure you have a C compiler (gcc)
    echo 3. Check that NASM is installed
    echo 4. Run from MSYS2 terminal if on Windows
    exit /b 1
)
