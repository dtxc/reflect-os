#include <io.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <math.h>
#include <malloc.h>
#include <kheap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <paging.h>

#include <hw/keyboard.h>

void panic(char *fmt, ...) {
    char *str;

    va_list arg;
    va_start(arg, fmt);
    vsprintf(str, fmt, arg);
    va_end(arg);

    clear();
    printf("-----------kernel panic----------\n%s\n-------end of kernel panic-------", str);
    disable_cursor();

    asm volatile("cli");
    while (1) {
        asm volatile("hlt");
    }
}

void reboot() {
    asm volatile("cli");

    u32 temp;
    while ((temp & 0x02) != 0) {
        temp = inb(0x64);
        if ((temp & 0x01) != 0) {
            inb(0x60);
        }
    }
    outb(0x64, 0xFE);
    while (1);
}

int system(char *cmd) {
    printf("\n");
    cmd = trim(cmd);
    char **argv;
    int argc = split(cmd, ' ', &argv);

    if (strcmp(argv[0], "clear")) {
        clear();
        printf(">> ");
        return EXIT_SUCCESS;
    } else if (strcmp(argv[0], "reboot")) {
        reboot();
        return EXIT_SUCCESS;
    } else if (strcmp(argv[0], "echo")) {
        if (argc == 1) {
            print("echo: repeats your text\n\tUsage: echo <text>\n>> ");
            return ERR_NO_ARGS;
        }

        for (int i = 1; i < argc; i++) {
            print(argv[i]);
            printc(' ');
        }

        print("\n>> ");
        return EXIT_SUCCESS;
    } else if (strcmp(argv[0], "rand")) {
        if (argc == 1) {
            printf("%d", rand());
        } else {
            int max = atoi(argv[1]);
            printf("%d", rand() % max);
        }
        print("\n>> ");
        return EXIT_SUCCESS;
    } else if (strcmp(argv[0], "panic")) {
        panic("manually initiated panic");
        return EXIT_SUCCESS;
    } else if (strcmp(argv[0], "help")) {
        print("Command list:\n\tclear - clears the screen\n\treboot - reboots the system\n\techo <text> - repeats your text\n\trand - returns a random number\n>> ");
        return EXIT_SUCCESS;
    }

    printf("Unknown command: %s\n>> ", argv[0]);
    return ERR_CMD_NOTFOUND;
}

void start_kernel() {
    clear();

    init_gdt();
    init_idt();
    init_paging();
    init_dynamic_mem();
    init_keyboard();

    print("Copyright (c) thatOneArchUser 2022-2023\n\nType 'help' for a command list\n>> ");
    while (1);
}

