#pragma once

#include <common.h>

typedef struct {
    u16 lim_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();
void set_gdt_gate(u8 num, u32 base, u32 lim, u8 access, u8 gran);