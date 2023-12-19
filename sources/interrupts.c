#include "interrupts.h"

idt_gate_t	idt[IDT_ENTRIES] = {0};

static const char *interrupt_exception_message[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
};

/// Set IDT gate for interrupt handler at index `n`
///
/// ## Parameters
///
/// - `n` - index of interrupt handler
/// - `handler` - address of interrupt handler
///
/// ## Examples
///
/// ```
/// set_idt_gate(0x20, (uint32_t)isr32);
/// ```
///
/// ## Note
///
/// - `n` must be less than `IDT_ENTRIES`
/// - `handler` must be a valid address
void set_idt_gate(int n , uint32_t handler)
{
	idt[n].low_offset = LOW_B16(handler);
	idt[n].selector = KERNEL_CS;
	idt[n].__zero = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = HIGH_B16(handler);
}

void isr_handler(registers_t reg) 
{
	term_puts("received interrupt: ");
	term_puts(interrupt_exception_message[reg.int_no]);
	term_putc('\n');
}

void isr_install()
{
	// set_idt_gate(0, );
	// set_idt_gate(1, );
	// set_idt_gate(2, );
}
