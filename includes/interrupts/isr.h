#ifndef KERNEL_INTERRUPTS_ISR_H
#define KERNEL_INTERRUPTS_ISR_H

typedef struct registers {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
} __attribute__((packed)) registers_t;

typedef struct stack_state {
	uint32_t error_code;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
} __attribute__((packed)) stack_state_t;

void	isr_callbacks(registers_t regs, uint8_t interrupt, struct stack_state stack);

#endif
