#include "timer.h"
#include "ports.h"
#include "interrupts.h"

static volatile uint32_t timer_ticks = 0;

void timer_init(void) {
    // Set up PIT (Programmable Interval Timer) to fire at 1000Hz
    uint32_t divisor = 1193180 / TIMER_FREQUENCY;
    
    // Set command byte: channel 0, access mode 3, operating mode 3
    outb(0x43, 0x36);
    
    // Set frequency divisor
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
    
    // Install timer interrupt handler (IRQ0)
    // idt_set_gate(32, (uint32_t)timer_handler, 0x08, 0x8E);
}

void timer_handler(void) {
    timer_ticks++;
    
    // Send End of Interrupt to PIC
    outb(0x20, 0x20);
}

uint32_t get_uptime_seconds(void) {
    return timer_ticks / TIMER_FREQUENCY;
}

uint32_t get_uptime_ms(void) {
    return timer_ticks;
}

void delay_ms(uint32_t ms) {
    uint32_t start = timer_ticks;
    while ((timer_ticks - start) < ms) {
        asm volatile("hlt"); // Wait for interrupt
    }
}

void print_uptime(void) {
    uint32_t total_seconds = get_uptime_seconds();
    uint32_t hours = total_seconds / 3600;
    uint32_t minutes = (total_seconds % 3600) / 60;
    uint32_t seconds = total_seconds % 60;
    
    // Simple printf replacement for uptime
    char buffer[32];
    
    // Convert hours to hex
    buffer[0] = '0';
    buffer[1] = 'x';
    if (hours < 16) {
        buffer[2] = '0' + hours;
        buffer[3] = 'h';
        buffer[4] = ' ';
        buffer[5] = '\0';
    } else {
        buffer[2] = 'A' + (hours - 10);
        buffer[3] = 'h';
        buffer[4] = ' ';
        buffer[5] = '\0';
    }
    
    // Print hours
    extern void vga_print(const char* data);
    vga_print(buffer);
    
    // Print minutes
    buffer[0] = '0';
    buffer[1] = 'x';
    if (minutes < 16) {
        buffer[2] = '0' + (minutes / 10);
        buffer[3] = '0' + (minutes % 10);
    } else {
        buffer[2] = 'A' + (minutes / 16);
        buffer[3] = '0' + (minutes % 16);
    }
    buffer[4] = 'm';
    buffer[5] = ' ';
    buffer[6] = '\0';
    vga_print(buffer);
    
    // Print seconds
    buffer[0] = '0';
    buffer[1] = 'x';
    if (seconds < 16) {
        buffer[2] = '0' + (seconds / 10);
        buffer[3] = '0' + (seconds % 10);
    } else {
        buffer[2] = 'A' + (seconds / 16);
        buffer[3] = '0' + (seconds % 16);
    }
    buffer[4] = 's';
    buffer[5] = '\0';
    vga_print(buffer);
}
