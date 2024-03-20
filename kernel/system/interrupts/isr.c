#include "system/interrupts.h"
#include "memory/memory.h"

typedef void (*isr_handler_t)(registers_t, stack_state_t);

void isr_callbacks(registers_t regs, uint8_t interrupt, stack_state_t stack)
{
	static isr_handler_t handlers[IDT_SIZE] = {
		[INTERRUPT_PAGE_FAULT]	= isr_page_fault,
		[INTERRUPT_KEYBOARD]	= isr_keyboard,
	};

	if (handlers[interrupt] != NULL) {
		handlers[interrupt](regs, stack);
		pic_ack(interrupt);
	}
}
EXPORT_SYMBOL(isr_callbacks);
