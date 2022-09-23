/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserved
*/

#include "ports.h"

void reboot() {
    asm volatile("cli");
    unsigned temp;
    do {
        temp = port_byte_in(0x64);
        if ((temp & 0x01) != 0) {
            (void)port_byte_in(0x60);
            continue;
        } 
    } while ((temp & 0x02) != 0);
    port_byte_out(0x64, 0xFE);
    while (1);
}

void shutdown() {
    for (char *q = "Shutdown"; *q; ++q) port_byte_out(0x8900, *q);
    port_byte_out(0xf4, 0x00); //if above function fails
}