#include "symbol_table.h"
#include "interrupt/interrupts.h"
#include "memory/memory.h"

IDT_t		g_idt = {0};
IDT_entry_t	g_idt_entries[IDT_ENTRIES_SIZE] = {0};

/// Set IDT descriptor for interrupt handler at `index`
///
/// ## Parameters
///
/// - `index` - index of interrupt handler
/// - `isr` - address of interrupt handler
///
/// ## Examples
///
/// ```
/// set_idt_gate(0x20, (uint32_t)isr32);
/// ```
///
/// ## Note
///
/// - `n` must be less than `IDT_ENTRIES_SIZE`
/// - `handler` must be a valid address
void set_idt_descriptor(int index, uint32_t isr) //! idt_set_gate
{
	g_idt_entries[index].base_low = LOW_B16(isr);
	g_idt_entries[index].base_high = HIGH_B16(isr);
	g_idt_entries[index].selector = KERNEL_CODE_SEG;
	g_idt_entries[index].zero = 0;
	g_idt_entries[index].flags = 0x8E;
}
EXPORT_SYMBOL(set_idt_descriptor);

/// Initialize Interrupt Descriptor Table (IDT)
void interrupts_init(void)
{
	g_idt.size = (sizeof(IDT_entry_t) * IDT_ENTRIES_SIZE) - 1;
	g_idt.address = (uint32_t)&g_idt_entries;

	memset(&g_idt_entries, 0, sizeof(IDT_entry_t) * IDT_ENTRIES_SIZE);

	set_idt_descriptor(INTERRUPT_PAGE_FAULT, (uint32_t)interrupt_handler_14);
	// set_idt_descriptor(INTERRUPT_TIMER, (uint32_t)interrupt_handler_32);
	set_idt_descriptor(INTERRUPT_KEYBOARD, (uint32_t)interrupt_handler_33);
	// set_idt_descriptor(INTERRUPT_SYSCALL, (uint32_t)interrupt_handler_128);
	idt_load((uint32_t)&g_idt);

	pic_remap(PIC_MASTER_OFFSET, PIC_SLAVE_OFFSET);
}
EXPORT_SYMBOL(interrupts_init);

/// Call handler corresponding to interrupt
void interrupt_handler(registers_t regs, unsigned int interrupt, stack_state_t stack)
{
	void (*handlers[IDT_ENTRIES_SIZE])(registers_t, stack_state_t) = {
		[INTERRUPT_PAGE_FAULT] = page_fault_handler,
		[INTERRUPT_KEYBOARD] = keyboard_handler,
	};

	if (interrupt < IDT_ENTRIES_SIZE && handlers[interrupt]) {
		handlers[interrupt](regs, stack);
		pic_acknowledge(interrupt);
	}
}
EXPORT_SYMBOL(interrupt_handler);