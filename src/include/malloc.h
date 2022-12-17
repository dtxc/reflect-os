#pragma once

#include <common.h>

#define DYNAMIC_MEM_SIZE 4096
#define MEM_NODE_SIZE sizeof(mem_node_t)

typedef struct mem_node {
    u32 size;
    bool used;
    struct mem_node *next;
    struct mem_node *prev;
} mem_node_t;

void init_dynamic_mem();
void *malloc(u32 size);
void free(void *p);