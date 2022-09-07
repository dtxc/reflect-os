/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include <mem.h>
#include <idt.h>
#include <isr.h>
#include <ports.h>
#include <types.h>
#include <timer.h>
#include <string.h>
#include <hal/hal.h>

#include "kernel.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

static char command[256];

void start_kernel() {
    print_string("Installing interrupt service routines\n");
    isr_install();

    print_string("Enabling external interrupts\n");
    asm volatile("sti");

    print_string("Initializing keyboard\n");
    init_keyboard();

    print_string("Initializing dynamic memory\n");
    init_dynamic_mem();

    clear_screen();
    print_string("Welcome to theroid os!\ntype help for a command list\n");
    print_string(">> ");
}

void save_command(char cmd[]) {
    command[0] = '\0';
    for (int i = 0; i < string_length(cmd); i++) {
        append(command, cmd[i]);
    }
}

void execute_command(char *input) {
    print_nl();
    input = trim(input);
    save_command(input);
    if (compare_string(input, "halt") || compare_string(input, "shutdown")) {
        shutdown();
    } else if (compare_string(input, "clear")) {
        clear_screen();
        print_string(">> ");
    } else if (compare_string(input, "help")) {
        print_string(
            "halt - stops the system\n"
            "clear - clears the screen\n"
            "echo <text> - prints text\n"
            "panic - triggers a kenrel panic\n"
            "reboot - reboots the system by causing a triple cpu fault\n"
        );
        print_string(">> ");
    } else if (startswith(input, "echo")) {
        char **arr = 0;
        int tokens = split(input, ' ', &arr);
        for (int i = 1; i < tokens; i++) {
            print_string(trim(arr[i]));
            print_string(" ");
        }
        print_nl();
        print_string(">> ");
    } else if (startswith(input, "panic")) {
        panic(MANUALLY_INITIATED_PANIC, "e");
    } else if (compare_string(input, "reboot")) {
        reboot();
    } else if (compare_string(input, "qw")) {
        asm volatile("int %0" : : "i"(0x14));
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

void panic(panicreason_t reason, char *message) {
    clear_screen();
    print_string("----beginning of kernel panic----\n\n");
    print_string(message);
    print_string("\n\n-------end of kernel panic-------\n");
    switch (reason) {
        case INTERRUPT_EXCEPTION: {
            print_string("Kernel panic: unhandled interrupt exception");
            break;
        }
        case ROOT_MOUNT_FAILED: {
            print_string("Kernel panic: failed to mount root device");
            break;
        }
        case MANUALLY_INITIATED_PANIC: {
            print_string("Kernel panic: manually initiated panic");
            break;
        }
        default: {
            print_string("Kernel panic: unknown exception");
        }
    }
    asm volatile("cli");
    asm volatile("hlt");
}
