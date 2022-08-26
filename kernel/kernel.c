/* TODO:
        beep sound at interrupt exception
        left/right arrow support
        filesystem
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

void reboot() {
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
        print_string("Disabling interrupts...");
        asm volatile("cli");
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
    } else if (compare_string(input, "printmem") == 0) {
        print_dynamic_mem();
        print_nl();
        print_string(">> ");
    } else if (startswith(input, "interrupt")) {
        asm volatile("int %0" : : "i"(0x14));
    } else if (compare_string(input, "reboot") == 0) {
        //asm volatile("jmp far ptr 0FFFFh:0");
        reboot();
    } else if (compare_string(input, "q") == 0) {
        print_string("\33[2K");
    }
    else {
        print_string("Unknown command: ");
        print_string(input);
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
