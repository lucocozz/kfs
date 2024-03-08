#include "interrupts/interrupts.h"
#include "memory/memory.h"

void isr_callbacks(registers_t regs, uint8_t interrupt, stack_state_t stack)
{
	static void (*handlers[IDT_SIZE])(registers_t, stack_state_t) = {
		[INTERRUPT_PAGE_FAULT]	= page_fault_handler,
		[INTERRUPT_KEYBOARD]	= keyboard_handler,
	};

	if (handlers[interrupt] != NULL) {
		handlers[interrupt](regs, stack);
		pic_ack(interrupt);
	}
}
EXPORT_SYMBOL(isr_callbacks);
