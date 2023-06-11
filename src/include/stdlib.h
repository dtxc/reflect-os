#pragma once

#include <stdarg.h>
#include <common.h>

#define EXIT_SUCCESS 0

#define ERR_NO_ARGS      1
#define ERR_CMD_NOTFOUND 127

int system(char *cmd);
void vsprintf(char *dest, char *fmt, va_list list);
void sprintf(char *dest, char *fmt, ...);