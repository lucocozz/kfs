#include "kernel.h"

void pic_acknowledge(unsigned int irq)
{
	if (irq >= PIC_MASTER_OFFSET && irq <= PIC_SLAVE_END)
	{
		if (irq < PIC_SLAVE_OFFSET)
			outb(PIC_MASTER, PIC_ACKNOWLEDGE);
		else
			outb(PIC_SLAVE, PIC_ACKNOWLEDGE);
	}
}
EXPORT_SYMBOL(pic_acknowledge);

void pic_remap(uint8_t offset1, uint8_t offset2)
{
	outb(PIC_MASTER, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	outb(PIC_SLAVE, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	outb(PIC_MASTER_DATA, offset1);
	outb(PIC_SLAVE_DATA, offset2);
	outb(PIC_MASTER_DATA, 4);
	outb(PIC_SLAVE_DATA, 2);

	outb(PIC_MASTER_DATA, PIC_ICW4_8086);
	outb(PIC_SLAVE_DATA, PIC_ICW4_8086);

	outb(PIC_MASTER_DATA, INTERRUPT_MASK_KEYBOARD);
	outb(PIC_SLAVE_DATA, INTERRUPT_MASK_RESERVED);

	ASM("sti");
}
EXPORT_SYMBOL(pic_remap);