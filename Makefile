# Build configuration
AS = nasm

# Try to use cross-compiler first, fallback to regular GCC
ifeq ($(shell which i686-elf-gcc 2>/dev/null),)
    CC = gcc
    LD = ld
    CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR) -m32
    LDFLAGS = -T linker.ld -m elf_i386 -nostdlib
else
    CC = i686-elf-gcc
    LD = i686-elf-ld
    CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR)
    LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
endif

# Directories
BUILD_DIR = build
BOOT_DIR = boot
KERNEL_DIR = kernel
INCLUDE_DIR = include

# Flags
ASFLAGS = -f bin

# Source files
BOOT_SRC = $(BOOT_DIR)/boot.asm
KERNEL_C_SRC = $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_ASM_SRC = $(wildcard $(KERNEL_DIR)/*.asm)

# Object files
KERNEL_C_OBJ = $(KERNEL_C_SRC:$(KERNEL_DIR)/%.c=$(BUILD_DIR)/%.o)
KERNEL_ASM_OBJ = $(KERNEL_ASM_SRC:$(KERNEL_DIR)/%.asm=$(BUILD_DIR)/%.o)
KERNEL_OBJ = $(KERNEL_C_OBJ) $(KERNEL_ASM_OBJ)

# Output files
BOOTLOADER = $(BUILD_DIR)/boot.bin
KERNEL = $(BUILD_DIR)/kernel.bin
OS_IMAGE = $(BUILD_DIR)/cyberos.img

.PHONY: all clean run

all: $(OS_IMAGE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BOOTLOADER): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.asm | $(BUILD_DIR)
	$(AS) -f elf32 $< -o $@

$(KERNEL): $(KERNEL_OBJ) linker.ld | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $(KERNEL_OBJ) -o $@ -lgcc || $(CC) $(LDFLAGS) $(KERNEL_OBJ) -o $@ -lgcc

$(OS_IMAGE): $(BOOTLOADER) $(KERNEL) | $(BUILD_DIR)
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BOOTLOADER) of=$@ conv=notrunc
	dd if=$(KERNEL) of=$@ seek=1 conv=notrunc

run: $(OS_IMAGE)
	qemu-system-i386 -fda $(OS_IMAGE)

clean:
	rm -rf $(BUILD_DIR)

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the complete OS image"
	@echo "  clean   - Remove all build files"
	@echo "  run     - Build and run the OS in QEMU"
	@echo "  help    - Show this help message"
