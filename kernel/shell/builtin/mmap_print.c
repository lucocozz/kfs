#include "multiboot.h"
#include "printk.h"
#include "shell/builtin.h"

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

void mmap_print(void)
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
}
