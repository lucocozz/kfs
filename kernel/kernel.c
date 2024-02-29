#include "kernel.h"

multiboot_info_t	*g_boot_info = NULL;

static void	__init_kernel()
{
	// gdt_init();
	// interrupts_init();
	term_init();
	// paging_init();
}

void init_memory()
{
	for (unsigned int i = 0; i < g_boot_info->mmap_length; i += sizeof(struct multiboot_mmap_entry))
	{
		struct multiboot_mmap_entry *mmmt = (struct multiboot_mmap_entry*)(g_boot_info->mmap_addr + i + KERNEL_START);
		printk("Mmap entry: base_addr = 0x%08x%08x, length = 0x%08x%08x\n \tsize = 0x%x, type = 0x%x\n",
			(uint32_t)mmmt->addr_high, (uint32_t)mmmt->addr_low,
			(uint32_t)mmmt->len_high, (uint32_t)mmmt->len_low,
			(uint32_t)mmmt->size, (uint32_t)mmmt->type);
	}
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		return ;
	// display boot info
	g_boot_info = (multiboot_info_t*)((uint32_t)boot_info + KERNEL_START);
	__init_kernel();
	init_memory();
	// __asm__ volatile("sti");
	printk("Kernel initialized\n");
	// shell();
	PAUSE_RUNTIME;
}
EXPORT_SYMBOL(kernel_main);
