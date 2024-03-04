#include "kernel.h"

void pic_acknowledge(unsigned int interrupt)
{
	if (interrupt >= PIC_1_OFFSET && interrupt <= PIC_2_END)
	{
		if (interrupt < PIC_2_OFFSET)
			outb(PIC_1_COMMAND, PIC_ACKNOWLEDGE);
		else
			outb(PIC_2_COMMAND, PIC_ACKNOWLEDGE);
	}
}
EXPORT_SYMBOL(pic_acknowledge);

void pic_remap(uint8_t offset1, uint8_t offset2)
{
	outb(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	outb(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	outb(PIC_1_DATA, offset1);
	outb(PIC_2_DATA, offset2);
	outb(PIC_1_DATA, 4);
	outb(PIC_2_DATA, 2);

	outb(PIC_1_DATA, PIC_ICW4_8086);
	outb(PIC_2_DATA, PIC_ICW4_8086);

	outb(PIC_1_DATA, INTERRUPT_MASK_KEYBOARD);
	outb(PIC_2_DATA, INTERRUPT_MASK_RESERVED);

	ASM("sti");
}
EXPORT_SYMBOL(pic_remap);