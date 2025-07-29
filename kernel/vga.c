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

void vga_draw_box(size_t x, size_t y, size_t width, size_t height, enum vga_color color) {
    uint8_t old_color = vga_color;
    vga_color = vga_entry_color(color, VGA_COLOR_BLACK);
    
    // Draw top and bottom borders
    for (size_t i = 0; i < width; i++) {
        if (x + i < VGA_WIDTH) {
            if (y < VGA_HEIGHT) vga_putentryat(i == 0 ? '+' : (i == width-1 ? '+' : '-'), vga_color, x + i, y);
            if (y + height - 1 < VGA_HEIGHT) vga_putentryat(i == 0 ? '+' : (i == width-1 ? '+' : '-'), vga_color, x + i, y + height - 1);
        }
    }
    
    // Draw left and right borders
    for (size_t i = 1; i < height - 1; i++) {
        if (y + i < VGA_HEIGHT) {
            if (x < VGA_WIDTH) vga_putentryat('|', vga_color, x, y + i);
            if (x + width - 1 < VGA_WIDTH) vga_putentryat('|', vga_color, x + width - 1, y + i);
        }
    }
    
    vga_color = old_color;
}

void vga_fill_rect(size_t x, size_t y, size_t width, size_t height, char fill_char, enum vga_color color) {
    uint8_t old_color = vga_color;
    vga_color = vga_entry_color(color, VGA_COLOR_BLACK);
    
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if (x + col < VGA_WIDTH && y + row < VGA_HEIGHT) {
                vga_putentryat(fill_char, vga_color, x + col, y + row);
            }
        }
    }
    
    vga_color = old_color;
}

void vga_progress_bar(size_t x, size_t y, size_t width, uint8_t percentage, enum vga_color fill_color, enum vga_color bg_color) {
    uint8_t old_color = vga_color;
    size_t filled = (width * percentage) / 100;
    
    vga_color = vga_entry_color(bg_color, VGA_COLOR_BLACK);
    vga_putentryat('[', vga_color, x, y);
    vga_putentryat(']', vga_color, x + width + 1, y);
    
    for (size_t i = 0; i < width; i++) {
        if (x + 1 + i < VGA_WIDTH && y < VGA_HEIGHT) {
            if (i < filled) {
                vga_color = vga_entry_color(fill_color, VGA_COLOR_BLACK);
                vga_putentryat('#', vga_color, x + 1 + i, y);
            } else {
                vga_color = vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
                vga_putentryat('.', vga_color, x + 1 + i, y);
            }
        }
    }
    
    vga_color = old_color;
}

void vga_rainbow_text(const char* text, size_t x, size_t y) {
    enum vga_color colors[] = {VGA_COLOR_RED, VGA_COLOR_LIGHT_BROWN, VGA_COLOR_LIGHT_BROWN, 
                               VGA_COLOR_GREEN, VGA_COLOR_CYAN, VGA_COLOR_BLUE, VGA_COLOR_MAGENTA};
    uint8_t old_color = vga_color;
    
    for (size_t i = 0; text[i] != '\0' && x + i < VGA_WIDTH; i++) {
        vga_color = vga_entry_color(colors[i % 7], VGA_COLOR_BLACK);
        vga_putentryat(text[i], vga_color, x + i, y);
    }
    
    vga_color = old_color;
}

void vga_matrix_effect(void) {
    static uint32_t frame_counter = 0;
    frame_counter++;
    
    // Create falling characters effect
    for (int col = 0; col < VGA_WIDTH; col += 3) {
        if ((frame_counter + col) % 20 == 0) {
            uint8_t old_color = vga_color;
            vga_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
            
            char matrix_chars[] = "01アイウエオカキク";
            char random_char = matrix_chars[(frame_counter + col) % 16];
            
            // Draw falling character
            for (int row = 0; row < VGA_HEIGHT; row += 2) {
                if (row < VGA_HEIGHT - 1) {
                    vga_putentryat(' ', vga_color, col, row);
                    vga_putentryat(random_char, vga_color, col, row + 1);
                }
            }
            
            vga_color = old_color;
        }
    }
}

void vga_draw_cyber_logo(void) {
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    
    // Enhanced CyberOS logo with more detail
    vga_print("\n");
    vga_print("     ███████╗██╗   ██╗██████╗ ███████╗██████╗  ██████╗ ███████╗\n");
    vga_print("     ██╔════╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔══██╗██╔═══██╗██╔════╝\n");
    vga_print("     ██║      ╚████╔╝ ██████╔╝█████╗  ██████╔╝██║   ██║███████╗\n");
    vga_print("     ██║       ╚██╔╝  ██╔══██╗██╔══╝  ██╔══██╗██║   ██║╚════██║\n");
    vga_print("     ███████╗   ██║   ██████╔╝███████╗██║  ██║╚██████╔╝███████║\n");
    vga_print("     ╚══════╝   ╚═╝   ╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n");
    vga_print("\n");
    vga_set_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK);
    vga_print("        🔐 Cybersecurity Edition v3.0 - Built for Security Education\n");
    vga_print("\n");
    vga_set_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
    vga_print("            ┌─────────────────────────────────────────┐\n");
    vga_print("            │  \"Where Learning Meets Real Security\"   │\n");
    vga_print("            │                                         │\n");
    vga_print("            │  • Advanced OS Development              │\n");
    vga_print("            │  • Professional Security Tools          │\n");
    vga_print("            │  • Interactive Learning Platform        │\n");
    vga_print("            │  • Hands-on Cybersecurity Training     │\n");
    vga_print("            └─────────────────────────────────────────┘\n");
    vga_print("\n");
}
