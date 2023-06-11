#include <isr.h>
#include <syscall.h>

static void syscall_handler(regs_t *regs);

u32 nsyscalls = 3;

static void *syscalls[3] = {
    &printc,
    &print,
    &clear
};

DEFN_SYSCALL1(printc, 0, char);
DEFN_SYSCALL1(print, 1, char*);
DEFN_SYSCALL0(clear, 2);

void init_syscalls() {
    register_interrupt_handler(0x80, syscall_handler);
}

void syscall_handler(regs_t *regs) {
    if (regs->eax >= nsyscalls) {
        return;
    }

    void *location = syscalls[regs->eax];

    int ret;
    asm volatile(" \
        push %1; \
        push %2; \
        push %3; \
        push %4; \
        push %5; \
        call *%6; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));

    regs->eax = ret;
}