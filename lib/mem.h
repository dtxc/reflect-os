#pragma once

#include "../kernel/core/types.h"

#define NULL_POINTER ((void*)0)

void memory_copy(u8* source, u8* dest, u32 nbytes);
void init_dynamic_mem();
void test_dynamic_mem();
void print_dynamic_node_size();
void print_dynamic_mem();
void *mem_alloc(size_t size);
void mem_free(void* p);
void* alloc(TYPE_t t, int n);
