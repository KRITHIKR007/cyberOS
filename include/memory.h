#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

// Memory management
void memory_init(void);
void* kmalloc(size_t size);
void kfree(void* ptr);
uint32_t get_memory_usage(void);
uint32_t get_free_memory(void);

// Memory statistics
struct memory_stats {
    uint32_t total_memory;
    uint32_t used_memory;
    uint32_t free_memory;
    uint32_t allocated_blocks;
};

void get_memory_stats(struct memory_stats* stats);

#endif
