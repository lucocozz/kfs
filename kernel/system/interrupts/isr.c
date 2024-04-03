#include "system/interrupts.h"
#include "system/signals.h"
#include "../includes/memory.h"

typedef void (*isr_handler_t)(registers_t, stack_state_t);

void isr_divide_by_zero(registers_t regs, stack_state_t stack)
{
	UNUSED(stack);
	UNUSED(regs);
	do_signal(SIGFPE);
}
EXPORT_SYMBOL(isr_divide_by_zero);


void isr_callbacks(registers_t regs, uint8_t interrupt, stack_state_t stack)
{
	static isr_handler_t handlers[IDT_SIZE] = {
		[INTERRUPT_DIVIDE_BY_ZERO]	= isr_divide_by_zero,
		[INTERRUPT_PAGE_FAULT]		= isr_page_fault,
		[INTERRUPT_KEYBOARD]		= isr_keyboard,
	};

	if (handlers[interrupt] != NULL) {
		handlers[interrupt](regs, stack);
		pic_ack(interrupt);
	}
}
EXPORT_SYMBOL(isr_callbacks);
