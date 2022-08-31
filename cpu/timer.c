/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include "../kernel/kernel.h"

u32 tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
    print_string("Tick: ");

    char tick_ascii[256];
    int_to_string(tick, tick_ascii);
    print_string(tick_ascii);
    print_nl();
}

void init_timer(u32 freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
