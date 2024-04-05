#include "kernel.h"

static void	__init_kernel(multiboot_info_t *boot_info)
{
	term_init();
	idt_init();
	gdt_init();
	memory_sections_init(boot_info);
	memory_init();
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	__init_kernel(boot_info);
	printk("Kernel initialized\n");
	shell();
}
EXPORT_SYMBOL(kernel_main);
