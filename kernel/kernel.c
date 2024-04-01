#include "kernel.h"

static void	__init_kernel(multiboot_info_t *boot_info)
{
	term_init();
	gdt_init();
	idt_init();
	memory_sections_init(boot_info);
	memory_init();
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	__init_kernel(boot_info);
	mmap(1024);
	mmap(1024 * 2);
	// void *toto = mmap(1024);
	mmap(1024 * 2);
	// munmap(toto, 1024);
	print_free_list();
	shell();
}
EXPORT_SYMBOL(kernel_main);
