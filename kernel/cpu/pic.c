#include "kernel.h"

void pic_acknowledge(unsigned int interrupt)
{
	if (interrupt >= PIC_1_OFFSET && interrupt <= PIC_2_END)
	{
		if (interrupt < PIC_2_OFFSET)
			write_port(PIC_1_COMMAND, PIC_ACKNOWLEDGE);
		else
			write_port(PIC_2_COMMAND, PIC_ACKNOWLEDGE);
	}
}

void pic_remap(uint8_t offset1, uint8_t offset2)
{
	write_port(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	write_port(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	write_port(PIC_1_DATA, offset1);
	write_port(PIC_2_DATA, offset2);
	write_port(PIC_1_DATA, 4);
	write_port(PIC_2_DATA, 2);

	write_port(PIC_1_DATA, PIC_ICW4_8086);
	write_port(PIC_2_DATA, PIC_ICW4_8086);

	write_port(PIC_1_DATA, INTERRUPT_MASK_KEYBOARD);
	write_port(PIC_2_DATA, INTERRUPT_MASK_RESERVED);

	asm volatile("sti");
}