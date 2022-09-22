/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserved
*/

#include "mem.h"  //i dont use <> in includes because clangd gets confused
#include "idt.h"
#include "isr.h"
#include "rand.h"
#include "stdio.h"
#include "stdlib.h"
#include "ports.h"
#include "types.h"
#include "string.h"
#include "timer.h"
#include "kernel.h"

#include "hal/hal.h"
#include "../drivers/drive.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

void start_kernel() {
    clear_screen();
    printf("Initializing interrupt service routines\n");
    isr_install();

    printf("Enabling external interrupts\n");
    asm volatile("sti");

    printf("Initializing timer (IRQ 0)\n");
    init_timer(50);

    printf("[%u] Initializing keyboard (IRQ 1)\n", gettick());
    init_keyboard();

    printf("[%u] Initializing dynamic memory\n", gettick());
    init_dynamic_mem();

    printf("[%u] Initializing hard drive (IRQ 2, 3)\n", gettick());
    init_drive();

    printf("Welcome to theroid os!\ntype help for a command list\n>> ");
}

void execute_command(char *input) {
    print_nl();
    input = trim(input);
    if (strcmp(input, "halt") || strcmp(input, "shutdown")) {
        shutdown();
    } else if (strcmp(input, "clear")) {
        clear_screen();
        printf(">> ");
    } else if (strcmp(input, "help")) {
        printf(
            "halt - stops the system\n"
            "clear - clears the screen\n"
            "echo <text> - prints text\n"
            "panic - triggers a kenrel panic\n"
            "reboot - reboots the system by causing a triple cpu fault\n"
            ">> "
        );
    } else if (startswith(input, "echo")) {
        char **arr;
        int tokens = split(input, ' ', &arr);
        for (int i = 1; i < tokens; i++) {
            printf("%s ", arr[i]);
        }
        print_nl();
        printf(">> ");
    } else if (startswith(input, "panic")) {
        panic("e");
    } else if (strcmp(input, "reboot")) {
        reboot();
    } else if (strcmp(input, "rand")) {
        printf("%u", rand() % (rand() % rand()));
    }
    else {
        printf("Unknown command: %s\n>> ", input);
    }
}

void panic(char *message) {
    clear_screen();
    printf("----beginning of kernel panic----\n\n%s\n\n-------end of kernel panic-------\n", message);
    asm volatile("cli\nhlt");
}
