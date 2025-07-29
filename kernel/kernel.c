#include "vga.h"
#include "keyboard.h"
#include "interrupts.h"
#include "timer.h"
#include "memory.h"
#include "games.h"

void kernel_main(void) {
    // Initialize VGA display
    vga_init();
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_clear_screen();
    
    // Show cool boot logo
    display_cyberos_logo();
    
    // Initialize system components
    memory_init();
    timer_init();
    
    vga_print("\n\nSystem initialized successfully!\n");
    vga_print("Type 'help' for available commands.\n\n");
    vga_print("cyberos> ");
    
    // Initialize interrupts
    idt_init();
    
    // Initialize keyboard
    keyboard_init();
    
    // Enable interrupts
    asm volatile("sti");
    
    // Main kernel loop
    while (1) {
        // Process keyboard input
        keyboard_update();
        
        // Halt CPU until next interrupt
        asm volatile("hlt");
    }
}
