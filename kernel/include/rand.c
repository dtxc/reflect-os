/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserved
*/

#include "rand.h"
#include "string.h"
#include "timer.h"
#include "stdlib.h"

static u32 next = 1;
static const int a = 1103515245;
static const int b = 69420;  //this number can be anything
static const int m = 0x80000000; //max value

u32 rand() { 
    if (next == 0) {
        next = gettick();
    }
    next = (a * next + b) % m; //https://en.wikipedia.org/wiki/Pseudorandom_number_generator
    return next;
}

void srand(u32 seed) {
    next = seed;
}

/*
char *rand_string(u16 len, char *arr) { //not working very well
    if (strlen(arr) == 0) return nullptr;
    char *res;
    for (u16 i = 0; i < len; i++) {
        res[i] = arr[rand() % (strlen(arr) - 1)];
    }
    return res;
}
*/
