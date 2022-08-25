#include <stdbool.h>
#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "display.h"
#include "../lib/string.h"
#include "../kernel/kernel.h"
#include "../lib/mem.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define UP_ARROW 0x4C
#define SHIFT 0x2A
#define SHIFT_RELEASE 0xAA 

static char key_buffer[256];
static bool shift;

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii_shift[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
                         'u', 'i', 'o', 'p', '[', ']', '?', '>', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};


static void keyboard_callback(registers_t *regs) {
    unsigned char status;
    unsigned char scancode;
    char release;
    status = port_byte_in(0x64);
    if (status & 0x01) {
        scancode = port_byte_in(0x60);
        if (scancode == SHIFT || scancode == 54) {
            shift = true;
        }
        if (scancode == SHIFT_RELEASE || scancode == 0xB6) {
            shift = false;
        }
        if (scancode == BACKSPACE) {
            if (backspace(key_buffer)) {
                print_backspace();
            }
        }
        if (scancode == ENTER) {
            if (string_length(key_buffer) == 0) {
                print_nl();
                print_string(">> ");
            } else {
                execute_command(key_buffer);
                key_buffer[0] = '\0';
            }
        }
        if (scancode <= 57 && sc_ascii[scancode] != '?' && shift == false) {
            char letter = sc_ascii[(int) scancode];
            append(key_buffer, letter);
            char str[2] = {letter, '\0'};
            print_string(str);
            release = port_byte_in(0x60);
        }
        if (scancode <= 57 && sc_ascii[scancode] != '?' && shift == true) {
            char letter = sc_ascii_shift[(int) scancode];
            append(key_buffer, letter);
            char str[2] = {letter, '\0'};
            print_string(str);
            release = port_byte_in(0x60);
        }
    }
    port_byte_out(0x20, 0x20);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}

