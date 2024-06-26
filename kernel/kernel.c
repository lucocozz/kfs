#include "kernel.h"


void	sigfpe_handler(int signum)
{
	UNUSED(signum);
	panic("HANDLED Divide by zero");
}

void	test_signal(void)
{
	int a = 0;
	int b = 1;
	int c = b / a;
	UNUSED(c);
}

static void	__init_kernel(multiboot_info_t *boot_info)
{
	term_init();
	idt_init();
	signals_init();
	gdt_init();
	memory_sections_init(boot_info);
	memory_init();
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	__init_kernel(boot_info);

	// signal(SIGFPE, sigfpe_handler);
	// test_signal();
	
	printk("Kernel initialized\n");
	shell();
}
EXPORT_SYMBOL(kernel_main);
