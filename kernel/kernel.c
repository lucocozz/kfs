#include "kernel.h"

multiboot_info_t	*g_boot_info = NULL;

static void	__init_kernel(multiboot_info_t *boot_info)
{
	gdt_init();
	interrupts_init();
	term_init();
	// paging_init();
	g_boot_info = (multiboot_info_t*)((uint32_t)boot_info + KERNEL_START);
	g_boot_info->mmap_addr += KERNEL_START;
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	__init_kernel(boot_info);
	shell();
}
EXPORT_SYMBOL(kernel_main);
