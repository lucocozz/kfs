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

void panic(const char *format, ...)
{
	va_list ap;
	stack_state_t *stack;

	va_start(ap, format);
	printk("KERNEL PANIC");
	if (format != NULL) {
		printk(": ");
		vprintk(format, ap);
	}

	ASM("mov %%esp, %0" : "=r"(stack));	// to save a trace of the stack at panic
	__clean_registers();				// to avoid somes exceptions
	
	ASM("cli; hlt");
}
EXPORT_SYMBOL(panic);
