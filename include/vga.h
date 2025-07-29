#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void vga_init(void);
void vga_set_color(enum vga_color fg, enum vga_color bg);
void vga_putchar(char c);
void vga_print(const char* data);
void vga_clear_screen(void);
void vga_print_hex(uint32_t value);
void vga_putentryat(char c, uint8_t color, size_t x, size_t y);
uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);

// Advanced graphics functions
void vga_draw_box(size_t x, size_t y, size_t width, size_t height, enum vga_color color);
void vga_fill_rect(size_t x, size_t y, size_t width, size_t height, char fill_char, enum vga_color color);
void vga_progress_bar(size_t x, size_t y, size_t width, uint8_t percentage, enum vga_color fill_color, enum vga_color bg_color);
void vga_rainbow_text(const char* text, size_t x, size_t y);
void vga_matrix_effect(void);
void vga_draw_cyber_logo(void);

#endif
