/* TODO:
        interrupt message argument in interrupt command and interrupt message list accessed with "interrupt help"
        move execute_command in another file
        beep sound at interrupt exception
        reboot command
*/

#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/ports.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "../lib/mem.h"
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
    print_string("init_dynamic_mem()\n");
    print_dynamic_node_size();
    print_dynamic_mem();
    test_dynamic_mem();

    clear_screen();
    print_string("Welcome to theroid os!\ntype help for a command list\n");
    print_string(">> ");
}


void execute_command(char *input) {
    print_nl();
    save_command(input);
    if (compare_string(input, "halt") == 0 || compare_string(input, "exit") == 0) {
        print_string("System is going down for halt now!\n");
        asm volatile("hlt");
    } else if (compare_string(input, "clear") == 0) {
        clear_screen();
        print_string(">> ");
    } else if (compare_string(input, "memtest") == 0) {
        test_dynamic_mem();
        print_string(">> ");
    } else if (compare_string(input, "help") == 0) {
        print_string(
            "halt - stops the system\n"
            "clear - clears the screen\n"
            "memtest - tests dynamic memory allocation\n"
            "echo <text> - prints text\n"
            "printmem - prints dynamic memory allocation\n"
            "interrupt - triggers exception interrupt with code 0x14 (reserved)\n"
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
    } else if (compare_string(input, "printmem") == 0) {
        print_dynamic_mem();
        print_nl();
        print_string(">> ");
    } else if (startswith(input, "interrupt")) {
        asm volatile("int %0" : : "i"(0x14));
    } else if (compare_string(input, "command") == 0) {
        print_string(get_previous_command());
        print_nl();
        print_string(">> ");
    }
    else {
        print_string("Unknown command: ");
        print_string(input);
        print_nl();
        print_string("\n>> ");
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
