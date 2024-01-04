#include "kernel.h"

IDT_t			idt = {0};
IDTDescriptor_t	idt_descriptors[IDT_ENTRIES] = {0};

/// Set IDT descriptor for interrupt handler at index `n`
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
void set_idt_descriptor(int n , uint32_t handler)
{
	idt_descriptors[n].offset_low = LOW_B16(handler);
	idt_descriptors[n].segment_selector = KERNEL_CODE_SEG;
	idt_descriptors[n].__reserved = 0;
	idt_descriptors[n].type_and_attr = 0x8E;
	idt_descriptors[n].offset_high = HIGH_B16(handler);
}

/// Initialize Interrupt Descriptor Table (IDT)
void interrupts_init()
{
	idt.size = sizeof(IDTDescriptor_t) * IDT_ENTRIES;
	idt.address = (uint32_t)idt_descriptors;

	// set_idt_descriptor(INTERRUPT_TIMER, (uint32_t)interrupt_handler_32);
	set_idt_descriptor(INTERRUPT_KEYBOARD, (uint32_t)interrupt_handler_33);
	// set_idt_descriptor(INTERRUPT_SYSCALL, (uint32_t)interrupt_handler_128);
	load_idt((uint32_t)&idt);

	pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}

/// Call handler corresponding to interrupt
void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack)
{
	void (*handlers[IDT_ENTRIES])(void) = {
		[INTERRUPT_KEYBOARD] = keyboard_handler,
	};

	(void)cpu;
	(void)stack;
	if (interrupt < IDT_ENTRIES && handlers[interrupt]) {
		handlers[interrupt]();
		pic_acknowledge(interrupt);
	}
}
