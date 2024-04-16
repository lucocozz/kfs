#ifndef KERNEL_INTERRUPTS_IRQ_H
#define KERNEL_INTERRUPTS_IRQ_H

void	irq_0(); // divide by zero
void	irq_13(); // general protection fault
void	irq_14(); // page fault
void	irq_32(); // timer
void	irq_33(); // keyboard
void	irq_128(); // system call

#endif
