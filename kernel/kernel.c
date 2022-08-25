// TODO: command history

#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/ports.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "../lib/mem.h"
#include "kernel.h"

static char *command;

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
    print_string("this is a welcome message\ntype HELP for help\n");
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
        print_string("halt - stops the system\nclear - clears the screen\nmemtest - tests dynamic memory allocation\necho <text> - prints text\nprintmem - prints dynamic memory allocation");
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
    } else if (startswith(input, "crash")) {
        asm volatile("int %0" : : "i"(0x0E));
    } else {
        print_string("Unknown command: ");
        char *ptr = alloc(CHAR, string_length(input));
        for (int i = 0; i < string_length(input); i++) {
            ptr[i] = input[i];
            if (input[i] == *" ") {
                break;
            }
        }
        print_string(ptr);
        mem_free(ptr);
        print_string("\n>> ");
    }
}

char *get_previous_command() {
    return command;
}

void save_command(char *cmd) {
    command = null;
    for (int i = 0; i < string_length(cmd); i++) {
        append(command, cmd[i]);
    }
}
