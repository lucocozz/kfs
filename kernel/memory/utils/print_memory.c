#include "system/utils.h"

#define HEX_SPACING		"  "
#define LINE_SPACING	"    "
#define BYTE_SPACING	" "


static void	__print_hexa_line(uint8_t *mem, uint size)
{
	uint i;

	for (i = 0; i < 16 && i < size; ++i) {
		printk("%x", mem[i]);
		if (i % 2 != 0)
			printk(BYTE_SPACING);
	}
	for (; i < 16; ++i) {
		printk(HEX_SPACING);
		if (i % 2 != 0)
			printk(BYTE_SPACING);
	}
	printk(" ");
	for (i = 0; i < 16 && i < size; ++i) {
		if (mem[i] >= 32 && mem[i] <= 126)
			printk("%c", mem[i]);
		else
			printk(".");
	}
	printk("\n");
}

void	print_memory(void *address, uint size)
{
	uint8_t	*mem = (uint8_t*)address;

	for (uint offset = 0; offset < size; offset += 16) {
		printk(LINE_SPACING "%p" HEX_SPACING, mem + offset);
		__print_hexa_line(mem + offset, size - offset);
	}
}
