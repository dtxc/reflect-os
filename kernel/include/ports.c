/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include <ports.h>

uchar port_byte_in(u16 port) {
    uchar result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(u16 port, u8 data) {
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}