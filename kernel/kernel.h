/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#pragma once

#include "core/ports.h"
#include "core/types.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../lib/mem.h"
#include "../lib/string.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

static char clipboard[256];

typedef enum {
    INTERRUPT_EXCEPTION,
    ROOT_MOUNT_FAILED
} panicreason_t;

void reboot();
void shutdown();
void execute_command(char *input);
char *get_previous_command();
void save_command(char *command);
void panic(panicreason_t reason, char *message);