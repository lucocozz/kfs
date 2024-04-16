#include "printk.h"
#include "symbol_table.h"

#define MAX_FRAMES 10

struct stackframe {
  struct stackframe* ebp;
  uint32_t eip;
};


static void	__print_register(uint32_t *reg, char *name)
{
	char	*symbol = symbol_lookup_addr((uint32_t)reg);

	printk("  %s = %08p", name, reg);
	if (symbol != NULL)
		printk(" <%s>", symbol);
	printk("\n");
}

void dump_stack(void)
{
    struct stackframe *stack;

    asm ("movl %%ebp,%0" : "=r"(stack) ::);
    printk("Stack dump:\n");
    for(unsigned int frame = 0; stack && frame < MAX_FRAMES; ++frame)
    {
      __print_register((uint32_t *)stack->eip, "eip");
      stack = stack->ebp;
    }
}
EXPORT_SYMBOL(dump_stack);
