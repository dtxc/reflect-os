#pragma once

#define ASSERT(b) ((b) ? (void) 0 : panic("%s, %d, %s", __FILE__, __LINE__, #b))

void panic(char *fmt, ...);