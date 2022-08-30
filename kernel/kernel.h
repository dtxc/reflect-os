#pragma once

void reboot();
void shutdown();
void execute_command(char *input);
char *get_previous_command();
void save_command(char *command);
