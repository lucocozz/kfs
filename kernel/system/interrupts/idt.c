#include "system/interrupts.h"
#include "memory/segments.h"

IDT_t		g_idt_ptr = {0};
IDT_entry_t	g_idt[IDT_SIZE] = {0};


void idt_set(uint8_t interrupt, uint32_t addr, uint8_t flags)
{
	g_idt[interrupt].addr_low = LOW_B16(addr);
	g_idt[interrupt].addr_high = HIGH_B16(addr);
	g_idt[interrupt].selector = 0x08;
	g_idt[interrupt].flags = flags;
	g_idt[interrupt]._reserved = 0;
}
EXPORT_SYMBOL(idt_set);

void idt_load(uint32_t idt_ptr)
{
	ASM("lidt (%0)" : : "r" (idt_ptr));
}
EXPORT_SYMBOL(idt_load);

void idt_init(void)
{
	g_idt_ptr.size = (sizeof(IDT_entry_t) * IDT_SIZE) - 1;
	g_idt_ptr.address = (uint32_t)&g_idt;

	IDT_SET_TRAP(INTERRUPT_DIVIDE_BY_ZERO, (uint32_t)irq_0);
	IDT_SET(INTERRUPT_PAGE_FAULT, (uint32_t)irq_14);
	IDT_SET(INTERRUPT_KEYBOARD, (uint32_t)irq_33); //? Perhaps consider changing this to directly use ISR or `isr_callbacks` instead of the IRQ overlay. This would significantly simplify the code, but it might be less modular.
	IDT_SET(INTERRUPT_SYSCALL, (uint32_t)irq_128);

	idt_load((uint32_t)&g_idt_ptr);

	pic_remap(PIC_MASTER_OFFSET, PIC_SLAVE_OFFSET);
}
EXPORT_SYMBOL(idt_init);
