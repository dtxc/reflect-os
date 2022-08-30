#pragma once

extern void shutdown();
extern void halt();

void reboot();
void shutdown();
void execute_command(char *input);
char *get_previous_command();
void save_command(char *command);
