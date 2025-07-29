#include "games.h"
#include "vga.h"
#include "keyboard.h"
#include "timer.h"
#include "memory.h"

void display_cyberos_logo(void) {
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
    vga_print("\n");
    vga_print(" ██████╗██╗   ██╗██████╗ ███████╗██████╗  ██████╗ ███████╗\n");
    vga_print("██╔════╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔══██╗██╔═══██╗██╔════╝\n");
    vga_print("██║      ╚████╔╝ ██████╔╝█████╗  ██████╔╝██║   ██║███████╗\n");
    vga_print("██║       ╚██╔╝  ██╔══██╗██╔══╝  ██╔══██╗██║   ██║╚════██║\n");
    vga_print("╚██████╗   ██║   ██████╔╝███████╗██║  ██║╚██████╔╝███████║\n");
    vga_print(" ╚═════╝   ╚═╝   ╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("\n    Advanced Operating System - Built for Cybersecurity\n");
}

void display_matrix_effect(void) {
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_clear_screen();
    
    const char matrix_chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZｦｧｨｩｪｫｬｭｮｯｰｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝ";
    
    for (int i = 0; i < 500; i++) {
        int x = i % 80;
        int y = (i / 80) % 25;
        
        char c = matrix_chars[i % (sizeof(matrix_chars) - 1)];
        vga_putentryat(c, vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK), x, y);
        
        if (i % 50 == 0) {
            delay_ms(100); // Animate the effect
        }
    }
    
    delay_ms(2000);
    vga_clear_screen();
    vga_print("Matrix effect complete! Welcome to CyberOS.\n");
}

void number_guessing_game(void) {
    vga_print("\n=== Number Guessing Game ===\n");
    vga_print("I'm thinking of a number between 1 and 100.\n");
    vga_print("Can you guess it?\n\n");
    
    // Simple pseudo-random number generator
    static uint32_t seed = 12345;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    int target = (seed % 100) + 1;
    
    int attempts = 0;
    int max_attempts = 7;
    
    vga_print("Enter your guess (or 'quit' to exit): ");
    
    // Note: This is a simplified version
    // In a real implementation, you'd need to read user input
    vga_print("\n[Game would accept user input here]\n");
    vga_print("Target number was: ");
    
    // Simple number to string conversion
    if (target >= 100) {
        vga_putchar('1');
        target -= 100;
    }
    if (target >= 10) {
        vga_putchar('0' + (target / 10));
        target %= 10;
    }
    vga_putchar('0' + target);
    vga_print("\n");
}

void snake_game(void) {
    vga_print("\n=== Snake Game ===\n");
    vga_print("Use WASD keys to move the snake.\n");
    vga_print("Eat the food (*) to grow!\n");
    vga_print("Don't hit the walls or yourself!\n\n");
    
    // Simple snake game visualization
    vga_print("┌────────────────────────────────────────┐\n");
    vga_print("│                                        │\n");
    vga_print("│  ####                                  │\n");
    vga_print("│                                        │\n");
    vga_print("│                   *                    │\n");
    vga_print("│                                        │\n");
    vga_print("│                                        │\n");
    vga_print("│                                        │\n");
    vga_print("└────────────────────────────────────────┘\n");
    vga_print("\nScore: 0  |  Length: 4\n");
    vga_print("\n[Full game implementation would go here]\n");
    vga_print("Press any key to return to main menu...\n");
}
