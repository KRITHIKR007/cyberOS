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
