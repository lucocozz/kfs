#include "kernel.h"
#include "multiboot.h"
#include "memory/memory_map.h"

static void	__init_kernel(multiboot_info_t *boot_info)
{
	gdt_init();
	interrupts_init();
	term_init();


	// Check flags
	init_memory_map(boot_info);
	get_memory_map();
	// paging_init();
}
EXPORT_SYMBOL(__init_kernel);

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	__init_kernel(boot_info);
	shell();
}
EXPORT_SYMBOL(kernel_main);
