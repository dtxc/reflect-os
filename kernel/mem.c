#include <stdbool.h>
#include <stdint.h>
#include "mem.h"
#include "../drivers/display.h"
#include "util.h"

typedef struct dynamic_mem_node {
    uint32_t size;
    bool used;
    struct dynamic_mem_node* next;
    struct dynamic_mem_node* prev;
} dynamic_mem_node_t;

#define DYNAMIC_MEM_TOTAL_SIZE 4096
#define DYNAMIC_MEM_NODE_SIZE sizeof(dynamic_mem_node_t)

static uint8_t dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dynamic_mem_node_t* dynamic_mem_start;

// malloc: http://www.sunshine2k.de/articles/coding/cmemalloc/cmemory.html#ch33

void memory_copy(uint8_t* source, uint8_t* dest, uint32_t nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void print_dynamic_node_size() { }

void print_dynamic_mem_node(dynamic_mem_node_t* node) { }

void print_dynamic_mem() { }

void* find_best_mem_block(dynamic_mem_node_t* dynamic_mem, size_t size) { }

void* mem_alloc(size_t size) { }

void* merge_next_node_into_current(dynamic_mem_node_t* current_mem_node) { }

void* merge_current_node_into_previous(dynamic_mem_node_t* current_mem_node) { }

void mem_free(void* p) { }
