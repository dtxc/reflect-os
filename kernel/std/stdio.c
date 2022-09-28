/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserved
*/
#include "types.h"
#include "hw/display.h"

static void _printdec(int n) {
    if (n == 0) print_string("0");
    if (n < 0) {
        print_string("-");
        n = -n;
    }

    u32 acc = n;
    char c[32];
    int i = 0;
    while (acc > 0) {
        c[i] = '0' + acc % 10;
        acc /= 10;
        i++;
    }
    c[i] = 0;
    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while (i >= 0) {
        c2[i--] = c[j++];
    }
    print_string(c2);
}

static void _printhex(u32 n) {
    int tmp;
    print_string("0x");

    bool bl;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && bl) continue;

        if (tmp >= 0xA) {
            bl = false;
            print_char(tmp - 0xA + 'a');
        } else {
            bl = false;
            print_char(tmp + '0');
        }
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) {
        print_char(tmp - 0xA + 'a');
    } else {
        print_char(tmp + '0');
    }
}

static void _vprintf(char *fmt, va_list list) {
    int i = 0;

    while (1) {
        char c = fmt[i];
        if (c == '\0') break;

        if (c == '%') {
            i++;
            char next = fmt[i];
            if (c == '\0') break;

            if (next == 'd') {
                int int_arg = va_arg(list, int);
                _printdec(int_arg);
            } else if (next == 'u') {
                u32 int_arg = va_arg(list, u32);
                _printdec(int_arg);
            } else if (next == 'x') {
                u32 int_arg = va_arg(list, u32);
                _printhex(int_arg);
            } else if (next == 'c') {
                char char_arg = va_arg(list, char);
                print_char(char_arg);
            } else if (next == 's') {
                char *str_arg = va_arg(list, char*);
                print_string(str_arg);
            }
        } else {
            print_char(c);
        }
        i++;
    }
}

void printf(char *str, ...) {
    va_list arg;
    va_start(arg, str);
    _vprintf(str, arg);
    va_end(arg);
}
