#pragma once

#include <paging.h>

#define KERNEL_STACK_SIZE 2048

typedef struct task {
    int id;
    u32 kernel_stack;
    regs_t regs;
    pagedir_t *dir;
    struct task *next;
    u8 state;
    u64 sleep_expiry;
} task_t;

void init_tasking();
void task_switch();
int fork();
int getpid();
void move_stack(void *new_stack_start, u32 size);
void switch_to_usermode();