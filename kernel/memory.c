#include "memory.h"
#include "string.h"

// Simple heap implementation
#define HEAP_START 0x200000  // 2MB mark
#define HEAP_SIZE 0x100000   // 1MB heap

struct heap_block {
    size_t size;
    int is_free;
    struct heap_block* next;
};

static struct heap_block* heap_head = NULL;
static uint32_t total_memory = HEAP_SIZE;
static uint32_t used_memory = 0;

void memory_init(void) {
    heap_head = (struct heap_block*)HEAP_START;
    heap_head->size = HEAP_SIZE - sizeof(struct heap_block);
    heap_head->is_free = 1;
    heap_head->next = NULL;
}

void* kmalloc(size_t size) {
    if (size == 0) return NULL;
    
    // Align to 4-byte boundary
    size = (size + 3) & ~3;
    
    struct heap_block* current = heap_head;
    
    while (current) {
        if (current->is_free && current->size >= size) {
            // Split block if it's much larger than needed
            if (current->size > size + sizeof(struct heap_block) + 16) {
                struct heap_block* new_block = (struct heap_block*)
                    ((char*)current + sizeof(struct heap_block) + size);
                new_block->size = current->size - size - sizeof(struct heap_block);
                new_block->is_free = 1;
                new_block->next = current->next;
                
                current->size = size;
                current->next = new_block;
            }
            
            current->is_free = 0;
            used_memory += current->size + sizeof(struct heap_block);
            return (char*)current + sizeof(struct heap_block);
        }
        current = current->next;
    }
    
    return NULL; // Out of memory
}

void kfree(void* ptr) {
    if (!ptr) return;
    
    struct heap_block* block = (struct heap_block*)((char*)ptr - sizeof(struct heap_block));
    block->is_free = 1;
    used_memory -= block->size + sizeof(struct heap_block);
    
    // Merge with next block if it's free
    if (block->next && block->next->is_free) {
        block->size += block->next->size + sizeof(struct heap_block);
        block->next = block->next->next;
    }
    
    // Merge with previous block if it's free
    struct heap_block* current = heap_head;
    while (current && current->next != block) {
        current = current->next;
    }
    
    if (current && current->is_free) {
        current->size += block->size + sizeof(struct heap_block);
        current->next = block->next;
    }
}

uint32_t get_memory_usage(void) {
    return used_memory;
}

uint32_t get_free_memory(void) {
    return total_memory - used_memory;
}

void get_memory_stats(struct memory_stats* stats) {
    stats->total_memory = total_memory;
    stats->used_memory = used_memory;
    stats->free_memory = total_memory - used_memory;
    
    // Count allocated blocks
    stats->allocated_blocks = 0;
    struct heap_block* current = heap_head;
    while (current) {
        if (!current->is_free) {
            stats->allocated_blocks++;
        }
        current = current->next;
    }
}
