// TODO: echo command

#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../lib/string.h"
#include "../lib/mem.h"

typedef enum {
    CHAR,
    INT,
    VOID
} TYPE;

void* alloc(TYPE t, int n) {
    void *ptr;
    switch (t) {
        case INT: {
            ptr = (int *) mem_alloc(n * sizeof(int));
            break;
        }
        case CHAR: {
            ptr = (char *) mem_alloc(n * sizeof(char));
            break;
        }
        case VOID: {
            ptr = (void *) mem_alloc(n * sizeof(void*));
        }
        default: {
            ptr = (void *) mem_alloc(n * sizeof(void*));
        }
    }
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

    int *ptr1 = alloc(INT, 5);
    print_string("int *ptr1 = alloc(5)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr2 = alloc(INT, 10);
    print_string("int *ptr2 = alloc(10)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr1);
    print_string("mem_free(ptr1)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr3 = alloc(INT, 2);
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
    print_string("this is a welcome message\ntype HELP for help\n");
    print_string(">> ");
}

void execute_command(char *input) {
    if (compare_string(input, "HALT") == 0 || compare_string(input, "EXIT") == 0) {
        print_string("System is going down for halt now!\n");
        asm volatile("hlt");
    } else if (compare_string(input, "CLEAR") == 0) {
        clear_screen();
        print_string(">> ");
    } else if (compare_string(input, "MEMTEST") == 0) {
        int *ptr = alloc(INT, 10);
        print_string("int *ptr = alloc(10)\n");
        print_dynamic_mem();
        print_nl();
        mem_free(ptr);
        print_string("mem_free(ptr)\n");
        print_dynamic_mem();
        print_nl();
        print_string(">> ");
    } else if (compare_string(input, "HELP") == 0) {
        print_string("HALT - stops the system\nCLEAR - clears the screen\nMEMTEST - tests dynamic memory allocation\nECHO <text> - prints text\n");
        print_string(">> ");
    } else if (startswith(input, "ECHO")) {
        // for (int i = 0; i < 4; i++){
        //     input = remove_by_index(input, 0);
        // }
        char out[string_length(input)+1];
        remove_by_index(input, out, 0);
        char *o = &out[0];
        for (int i = 0; i < string_length(out); i++) {
            print_string((o+i));
        }
        //print_string(out);
        print_nl();
        print_string(">> ");
    }
    else {
        print_string("Unknown command: ");
        print_string(input);
        print_string("\n>> ");
    }
}
