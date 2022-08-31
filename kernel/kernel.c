/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include "kernel.h"

static char command[256];

void start_kernel() {
    clear_screen();
    print_string("Installing interrupt service routines\n");
    isr_install();

    print_string("Enabling external interrupts\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1)\n");
    init_keyboard();

    print_string("Initializing dynamic memory\n");
    init_dynamic_mem();

    clear_screen();
    print_string("Welcome to theroid os!\ntype help for a command list\n");
    print_string(">> ");
}


void execute_command(char *input) {
    print_nl();
    save_command(input);
    if (compare_string(input, "exit") || compare_string(input, "shutdown")) {
        shutdown();
    } else if (compare_string(input, "clear")) {
        clear_screen();
        print_string(">> ");
    } else if (compare_string(input, "memtest")) {
        test_dynamic_mem();
        print_string(">> ");
    } else if (compare_string(input, "help")) {
        print_string(
            "halt - stops the system\n"
            "clear - clears the screen\n"
            "memtest - tests dynamic memory allocation\n"
            "echo <text> - prints text\n"
            "printmem - prints dynamic memory allocation\n"
            "interrupt - triggers interrupt exception with code 0x14 (reserved)\n"
            "reboot - reboots the system by causing a triple cpu fault\n"
        );
        print_string(">> ");
    } else if (startswith(input, "echo")) {
        char **arr = 0;
        int tokens = split(input, ' ', &arr);
        for (int i = 1; i < tokens; i++) {
            print_string(arr[i]);
            print_string(" ");
            mem_free(arr[i]);
        }
        print_nl();
        print_string(">> ");
    } else if (compare_string(input, "printmem")) {
        print_dynamic_mem();
        print_nl();
        print_string(">> ");
    } else if (startswith(input, "interrupt")) {
        asm volatile("int %0" : : "i"(0x14));
    } else if (compare_string(input, "reboot")) {
        reboot();
    } else {
        print_string("Unknown command: ");
        print_string(input);
        print_nl();
        print_string(">> ");
    }
}

char *get_previous_command() {
    return command;
}

void save_command(char cmd[]) {
    command[0] = '\0';
    for (int i = 0; i < string_length(cmd); i++) {
        append(command, cmd[i]);
    }
}

void panic(panicreason_t reason, char *message) {
    clear_screen();
    print_string("----beginning of kernel panic----\n");
    print_string(message);
    print_string("\n-------end of kernel panic-------\n");
    switch (reason) {
        case INTERRUPT_EXCEPTION: {
            print_string("Kernel panic: unhandled interrupt exception");
        }
        case ROOT_MOUNT_FAILED: {
            print_string("Kernel panic: failed to mount root device");
        }
        default: {
            print_string("Kernel panic: unknown exception");
        }
    }
    asm volatile("cli");
    asm volatile("hlt");
}