#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

// Timer frequency (1000 Hz = 1ms resolution)
#define TIMER_FREQUENCY 1000

void timer_init(void);
void timer_handler(void);
uint32_t get_uptime_seconds(void);
uint32_t get_uptime_ms(void);
void delay_ms(uint32_t ms);

#endif
