#include <vga.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void _printdec(int n) {
    if (n == 0) {
        printc('0');
        return;
    }
    if (n < 0) {
        printc('-');
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
    print(c2);
}

static void _printhex(int n) {
    if (n == 0) {
        print("00000000");
        return;
    }
    char res[12];
    int i = 0;

    while (n != 0) {
        int temp = 0;
        temp = n % 16;

        if (temp < 10) {
            res[i] = 48 + temp;
            i++;
        } else {
            res[i] = 55 + temp;
            i++;
        }
        n /= 16;
    }
    int zeros = 8 - strlen(res);
    for (int j = 0; j < zeros; j++) {
        printc('0');
    }
    for (int j = i - 1; j >= 0; j--) {
        printc(res[j]);
    }
}

void vprintf(char *fmt, va_list list) {
    int i = 0;

    while (1) {
        char c = fmt[i];
        if (c == '\0') {
            break;
        }

        if (c == '%') {
            i++;
            char next = fmt[i];
            if (c == '\0') {
                break;
            }

            if (next == 'd') {
                int int_arg = va_arg(list, int);
                _printdec(int_arg);
            } else if (next == 'u') {
                u32 uint_arg = va_arg(list, u32);
                char *buff;
                itoa(buff, uint_arg);
                print(buff);
            } else if (next == 'x') {
                u32 uint_arg = va_arg(list, u32);
                print("0x");
                _printhex(uint_arg);
            } else if (next == 'c') {
                char char_arg = va_arg(list, int);
                printc(char_arg);
            } else if (next == 's') {
                char *str_arg = va_arg(list, char*);
                print(str_arg);
            } else if (next == 'f') {
                double double_arg = va_arg(list, double);
                char buff[10];
                ftoa(double_arg, buff);
                print(buff);
            }
        } else {
            printc(c);
        }
        i++;
    }
}

void printf(char *str, ...) {
    va_list arg;
    va_start(arg, str);
    vprintf(str, arg);
    va_end(arg);
}