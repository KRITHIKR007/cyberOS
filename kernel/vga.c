#include "vga.h"

static uint16_t* const VGA_MEMORY = (uint16_t*)0xB8000;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t vga_row;
static size_t vga_column;
static uint8_t vga_color;

// Forward declaration
static void vga_scroll(void);

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void vga_init(void) {
    vga_row = 0;
    vga_column = 0;
    vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

void vga_set_color(enum vga_color fg, enum vga_color bg) {
    vga_color = vga_entry_color(fg, bg);
}

void vga_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    VGA_MEMORY[index] = vga_entry(c, color);
}

void vga_scroll(void) {
    // Move all lines up by one
    for (size_t i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        VGA_MEMORY[i] = VGA_MEMORY[i + VGA_WIDTH];
    }
    
    // Clear the last line
    for (size_t i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        VGA_MEMORY[i] = vga_entry(' ', vga_color);
    }
    
    vga_row = VGA_HEIGHT - 1;
    vga_column = 0;
}

void vga_putchar(char c) {
    if (c == '\n') {
        vga_column = 0;
        if (++vga_row == VGA_HEIGHT) {
            vga_scroll();
        }
        return;
    }
    
    vga_putentryat(c, vga_color, vga_column, vga_row);
    
    if (++vga_column == VGA_WIDTH) {
        vga_column = 0;
        if (++vga_row == VGA_HEIGHT) {
            vga_scroll();
        }
    }
}

void vga_print(const char* data) {
    for (size_t i = 0; data[i] != 0; i++) {
        vga_putchar(data[i]);
    }
}

void vga_clear_screen(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            VGA_MEMORY[index] = vga_entry(' ', vga_color);
        }
    }
    vga_row = 0;
    vga_column = 0;
}

void vga_print_hex(uint32_t value) {
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[11] = "0x00000000";
    
    for (int i = 9; i >= 2; i--) {
        buffer[i] = hex_chars[value & 0xF];
        value >>= 4;
    }
    
    vga_print(buffer);
}
