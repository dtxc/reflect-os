#include <io.h>
#include <isr.h>
#include <vga.h>
#include <string.h>

#include <hal/panic.h>

#define INTERRUPT_NUM 256
isr_t interrupt_handlers[INTERRUPT_NUM];

void clear_int() {
    memset(&interrupt_handlers, 0, sizeof(isr_t) * INTERRUPT_NUM);
}

void isr_handler(regs_t regs) {
    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(&regs);
    } else {
        printc(regs.int_no + 48);
        //panic("unhandled interrupt: %d\nerr_code: %d  ", regs.int_no, regs.err_code);
        //printf("unhandled interrupt: %d", regs.int_no);
        //printc(regs.int_no);
    }
}

void irq_handler(regs_t regs) {
    //send end of interrupt signal to pic
    if (regs.int_no >= 40) { //if the interrupt involved the slave
        //send reset signal to slave
        outb(PIC_SLAVE_CMD, PIC_EIO);
    }

    //send reset signal to master
    outb(PIC_MASTER_CMD, PIC_EIO);

    if (interrupt_handlers[regs.int_no] != 0) { //handle interrupt
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(&regs);
    }
}

void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void delete_interrupt_handler(u8 n) {
    interrupt_handlers[n] = 0;
}