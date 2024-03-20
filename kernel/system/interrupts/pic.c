#include "system/interrupts.h"

void	pic_ack(uint8_t irq)
{
	if (irq >= PIC_MASTER_OFFSET && irq <= PIC_SLAVE_END)
	{
		if (irq < PIC_SLAVE_OFFSET)
			outb(PIC_MASTER, PIC_ACKNOWLEDGE);
		else
			outb(PIC_SLAVE, PIC_ACKNOWLEDGE);
	}
}
EXPORT_SYMBOL(pic_ack);

void pic_remap(uint8_t offset1, uint8_t offset2)
{
	outb(PIC_MASTER, PIC_ICW1_INIT | PIC_ICW1_ICW4);
	outb(PIC_SLAVE, PIC_ICW1_INIT | PIC_ICW1_ICW4);
	outb(PIC_MASTER_DATA, offset1);
	outb(PIC_SLAVE_DATA, offset2);
	outb(PIC_MASTER_DATA, 4);
	outb(PIC_SLAVE_DATA, 2);

	outb(PIC_MASTER_DATA, PIC_ICW4_8086);
	outb(PIC_SLAVE_DATA, PIC_ICW4_8086);

	outb(PIC_MASTER_DATA, PIC_INTERRUPT_MASK_EXCEPT_KEYBOARD);
	outb(PIC_SLAVE_DATA, PIC_INTERRUPT_MASK_NONE);

	ASM("sti");
}
EXPORT_SYMBOL(pic_remap);
