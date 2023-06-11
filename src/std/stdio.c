#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

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
                char *p;
                itoa(p, int_arg);
                syscall_print(p);
            } else if (next == 'u') {
                u32 uint_arg = va_arg(list, u32);
                char *buff;
                itoa(buff, uint_arg);
                syscall_print(buff);
            } else if (next == 'x') {
                u32 uint_arg = va_arg(list, u32);
                char *p;
                int2hex(p, uint_arg);
                syscall_print(p);
            } else if (next == 'c') {
                char n = fmt[i + 1];
                if (n == 'p') {
                    i++;
                    complex_t cplx = va_arg(list, complex_t);
                    if (cplx.Re == 0) {
                        printf("%fi", cplx.Im);
                    } else if (cplx.Im == 0) {
                        printf("%f", cplx.Re);
                    } else {
                        printf("%f+%fi", cplx.Re, cplx.Im);
                    }
                } else {
                    char char_arg = va_arg(list, int);
                    syscall_printc(char_arg);
                }
            } else if (next == 's') {
                char *str_arg = va_arg(list, char*);
                syscall_print(str_arg);
            } else if (next == 'f') {
                double double_arg = va_arg(list, double);
                char buff[10];
                ftoa(buff, double_arg);
                syscall_print(buff);
            } else if (next == '%') {
                syscall_printc('%');
            }
        } else {
            syscall_printc(c);
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