#include "system/utils.h"

static void	__clean_registers(void)
{
	ASM(
		"xor %%eax, %%eax;"
		"xor %%ecx, %%ecx;"
		"xor %%edx, %%edx;"
		: : : "eax", "ecx", "edx"
	);
}

void panic(const char *msg)
{
	stack_state_t *stack;

	printk("KERNEL PANIC: %s\n", msg);
	
	ASM("mov %%esp, %0" : "=r"(stack));	// to save a trace of the stack at panic
	__clean_registers();				// to avoid somes exceptions
	
	ASM("cli; hlt");
}
EXPORT_SYMBOL(panic);
