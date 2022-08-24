#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "util.h"
#include "mem.h"

void* alloc(int n) {
    int *ptr = (int *) mem_alloc(n * sizeof(int));
    if (ptr == NULL_POINTER) {
        print_string("Memory not allocated\n");
    }
    return ptr;
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
    print_nl();

    int *ptr1 = alloc(5);
    print_string("int *ptr1 = alloc(5)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr2 = alloc(10);
    print_string("int *ptr2 = alloc(10)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr1);
    print_string("mem_free(ptr1)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr3 = alloc(2);
    print_string("int *ptr3 = alloc(2)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr2);
    print_string("mem_free(ptr2)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr3);
    print_string("mem_free(ptr3)\n");
    print_dynamic_mem();
    print_nl();

    clear_screen();
    print_string("this is a welcome message");
    print_string(">> ");
}

void execute_command(char *input) {
    if (compare_string(input, "HALT") == 0) {
        print_string("System is going down for halt now!\n");
        asm volatile("hlt");
    } else if (compare_string(input, "CLEAR") == 0) {
        clear_screen();
        print_string(">> ");
    } else if (compare_string(input, "MEMTEST") == 0) {
        int *ptr = alloc(10);
        print_string("int *ptr = alloc(10)");
        print_dynamic_mem();
        print_nl();
        mem_free(ptr);
        print_string("mem_free(ptr)\n");
        print_dynamic_mem();
        print_nl();
        print_string(">> ");
    } else if (compare_string(input, "HELP") == 0) {
        print_nl();
    } else if (startswith(input, "ECHO")) {
        char *result[2];
        //split_string(input, ' ', 1);
        print_string(result[1]);
        print_nl();
        print_string(">> ");
    }
    else {
        print_string("Unknown command: ");
        print_string(input);
        print_string("\n>> ");
    }
}
