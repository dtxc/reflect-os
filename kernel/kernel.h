/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#pragma once

static char clipboard[256];

typedef enum {
    INTERRUPT_EXCEPTION,
    ROOT_MOUNT_FAILED,
    MANUALLY_INITIATED_PANIC
} panicreason_t;


void execute_command(char *input);
char *get_previous_command();
void panic(panicreason_t reason, char *message);