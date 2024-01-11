#include "printk.h"
#include "symbol_table.h"

static void	__print_register(uint32_t *reg, char *name)
{
	char	*symbol = symbol_lookup_addr((uint32_t)reg);

	printk("  %s = %08p", name, reg);
	if (symbol != NULL)
		printk(" <%s>", symbol);
	printk("\n");
}
EXPORT_SYMBOL(__print_register);

void	dump_stack(void)
{
	uint32_t	*ebp, *eip, *esp;

	asm volatile (
		"mov %%ebp, %0;"
		"call 1f; 1: pop %1;"
		"mov %%esp, %2;"
		: "=r"(ebp), "=r"(eip), "=r"(esp)
	);

	printk("Stack dump:\n");
	for (size_t frame_index = 0; ebp != 0; ++frame_index)
	{
		printk("Frame %2d:\n", frame_index);
		__print_register(ebp, "ebp");
		__print_register(eip, "eip");
		__print_register(esp, "esp");
		ebp = (uint32_t*)*ebp;
		eip = (uint32_t*)*(ebp + 1);
		esp = ebp + 2;
	}
}
EXPORT_SYMBOL(dump_stack);
