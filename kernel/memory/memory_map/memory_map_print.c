#include "multiboot.h"
#include "printk.h"
#include "../includes/memory.h"


static void __print_device_info(void)
{
	uint32_t device = g_boot_info->boot_device >> 24;
	printk("BOOT DEVICE:\t");
	switch (device) {
	case 0xE0:
		printk("CD\n");
		break;
	case 0x00:
		printk("Floppy Disk\n");
		break;
	case 0x80:
		printk("Hard Disk\n");
		break;
	default:
		printk("Unknown\n");
		break;
	}
	printk("\n");
}

void memory_map_print(void)
{
	static const char *memory_types[] = {
		"Available",
		"Reserved",
		"ACPI Reclaimable",
		"ACPI NVS",
		"Bad RAM"
	};

	__print_device_info();
	printk("Memory Map:\n");
	printk("------------------------------------------------------------\n");
	printk("Base\t\t\t\t  Lenght\t\t\t\tType\n");
	printk("------------------------------------------------------------\n");
	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t))
	{
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);
		printk("0x%08X%08X\t0x%08X%08X\t%s\n",
			entry->addr_high, entry->addr_low,
			entry->len_high, entry->len_low,
			memory_types[entry->type - 1]
		);
	}
	printk("------------------------------------------------------------\n");

		// physical memory map
	printk("Kernel physical start  : 0x%X\n", g_memory_map.kernel.start - KERNEL_START);
	printk("Kernel physical end    : 0x%X\n", g_memory_map.kernel.end - KERNEL_START);
	printk("Kernel physical length : 0x%X\n", g_memory_map.kernel.length);
	printk("\n");

	// virtual memory map
	printk("Kernel virtual start   : 0x%X\n", g_memory_map.kernel.start);
	printk("Kernel virtual end     : 0x%X\n", g_memory_map.kernel.end);
	printk("Kernel virtual length  : 0x%X\n", g_memory_map.kernel.length);
	printk("\n");

	// Total memory
	printk("Memory Lower : %dKB\n", g_boot_info->mem_lower);
	printk("Memory Upper : %dKB\n", g_boot_info->mem_upper);
	printk("Total Memory : %dMB (lower + upper)\n", (g_boot_info->mem_lower + g_boot_info->mem_upper) / 1024);
}
EXPORT_SYMBOL(memory_map_print);