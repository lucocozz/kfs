#include "interrupts/interrupts.h"
#include "memory/memory.h"

void isr_callbacks(registers_t regs, uint8_t interrupt, stack_state_t stack)
{
	static void (*isr_handlers[IDT_SIZE])(registers_t, stack_state_t) = {
		[INTERRUPT_PAGE_FAULT]	= isr_page_fault,
		[INTERRUPT_KEYBOARD]	= isr_keyboard,
	};

	if (isr_handlers[interrupt] != NULL) {
		isr_handlers[interrupt](regs, stack);
		pic_ack(interrupt);
	}
}
EXPORT_SYMBOL(isr_callbacks);
