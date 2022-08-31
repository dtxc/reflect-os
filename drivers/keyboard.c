/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include "../kernel/kernel.h"

static char key_buffer[256];
static bool shift;
static bool alt;
static bool ctrl;

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii_shift[] = {'?', '?', '!', '@', '#', '$', '%', '^',
                         '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ':', '\"', '~', '/', '|', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
                         'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t *regs) {
    uchar status;
    u16 scancode;
    char release;
    status = port_byte_in(0x64);
    if (status & 0x01) {
        scancode = port_byte_in(0x60);
        if (scancode == SYSRQ) shutdown();
        if (ctrl && alt && scancode == DELETE) reboot();
        if (scancode == ALT) alt = true;
        if (scancode == ALT_RELEASE) alt = false;
        if (scancode == CTRL) ctrl = true;
        if (scancode == CTRL_RELEASE) ctrl = false;
        if (scancode == 0x2E && ctrl) { //copy
            clipboard[0] = '\0';
            for (int i = 0; i < string_length(key_buffer); i++) clipboard[i] = key_buffer[i];
        }
        if (scancode == 0x2F && ctrl) { //paste
            for (int i = 0; string_length(key_buffer) < 256 && i < string_length(key_buffer); i++) {
                append(key_buffer, clipboard[i]);
                print_string(&clipboard[i]);
            }
        }
        if (scancode == 0x2D && ctrl) { //cut
            clipboard[0] = '\0';
            for (int i = 0; i < string_length(key_buffer); i++) { 
                clipboard[i] = key_buffer[i];
                print_backspace();
            }
            key_buffer[0] = '\0';
        }
        if (scancode == HOME) {
            while (backspace(key_buffer)) set_cursor(get_cursor() - 1);
        }
        if (scancode == SHIFT || scancode == RSHIFT) shift = true;
        if (scancode == SHIFT_RELEASE || scancode == RSHIFT_RELEASE) shift = false;
        if (scancode == BACKSPACE) {
            if (backspace(key_buffer)) print_backspace();
        }
        if (scancode == UP_ARROW) {
            if (string_length(key_buffer) != 0) return;
            for (int i = 0; i < string_length(get_previous_command()); i++) {
                append(key_buffer, get_previous_command()[i]);
            }
            print_string(get_previous_command());
        }
        if (scancode == DOWN_ARROW) {
            if (compare_string(key_buffer, get_previous_command())) {
                for (int i = 0; i < string_length(key_buffer); i++) {
                    print_backspace();
                }
                key_buffer[0] = '\0';
            }
        }
        if (scancode == LEFT_ARROW) {
            if (backspace(key_buffer)) set_cursor(get_cursor()-1);
        }
        if (scancode == CAPS_LOCK) shift = !shift;
        if (scancode == ENTER) {
            if (string_length(key_buffer) == 0) {
                print_nl();
                print_string(">> ");
            } else {
                execute_command(key_buffer);
                key_buffer[0] = '\0';
            }
        }
        if (scancode == 0x47 && shift == true) {
            append(key_buffer, '?');
            print_string("?");
        }
        if (scancode <= 57 && sc_ascii[scancode] != '?') {
            if (string_length(key_buffer) == 256) return;
            char letter;
            if (shift) letter = sc_ascii_shift[(int) scancode];
            else letter = sc_ascii[(int) scancode];
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

