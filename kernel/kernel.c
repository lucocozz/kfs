#include "kernel.h"

multiboot_info_t	*g_boot_info = NULL;

void mmap_print(void)
{
	static const char *memory_types[] = {
		"Available",
		"Reserved",
		"ACPI Reclaimable",
		"ACPI NVS",
		"Bad RAM"
	};

	printk("Base\t\t\t\t  Lenght\t\t\t\tType\n");
	printk("------------------------------------------------------------\n");
	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t))
	{
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);
		printk("0x%08X%08X\t0x%08X%08X\t%s\n",
			entry->addr_high, entry->addr_low,
			entry->len_high, entry->len_low,
			memory_types[(uint32_t)entry->type - 1]
		);
	}
}

static void	__init_kernel(multiboot_info_t *boot_info)
{
	// gdt_init();
	// interrupts_init();
	term_init();
	// paging_init();
	g_boot_info = (multiboot_info_t*)((uint32_t)boot_info + KERNEL_START);
	g_boot_info->mmap_addr += KERNEL_START;
	mmap_print();
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		return ;
	__init_kernel(boot_info);
	// shell();
	PAUSE_RUNTIME;
}
EXPORT_SYMBOL(kernel_main);
