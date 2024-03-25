#include "../includes/memory.h"
#include "system/utils.h"
#include "symbol_table.h"

void	memory_init(void)
{
	printk("--------------------\n");
	printk("Physical Memory map\n");
	printk("--------------------\n");

	// uint32_t nb_of_mmap_entries = g_boot_info->mmap_length / sizeof(multiboot_mmap_entry_t);
    // multiboot_mmap_entry_t *mmap_entry = (multiboot_mmap_entry_t*)g_boot_info->mmap_addr + sizeof(multiboot_mmap_entry_t) * (nb_of_mmap_entries);
    // uint32_t total_memory = mmap_entry->addr_low + mmap_entry->len_low - 1;
	uint32_t total_memory = MAX_MEMORY_SIZE; // 4GB address space for 32 bits = 0xFFFFFFFF

    printk("Max memory size in bytes (for a 32 bits system): 0x%X \n", total_memory);
	// this is the nb blocks for the full 32 bits address space, we're mapping 4GB even if we have less memory
	printk("Total 4K blocks: 0x%x\n", total_memory * 1024 / FRAME_SIZE);

    initialise_memory_manager((uint32_t)&_kernel_end_physical, total_memory);

	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t))
	{
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);

		if(entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
            initialise_memory_region(entry->addr_low, entry->len_low);
		}
	}

	// set kernel memory as used and align it to 4K blocks above the kernel
	uint32_t kernel_memory_length = ((uint32_t)&_kernel_end_physical - (uint32_t)&_kernel_start_physical + FRAME_SIZE - 1) & ~(FRAME_SIZE - 1);
	deinitialise_memory_region((uint32_t)&_kernel_start_physical, kernel_memory_length);

	// reserve the memory map and align it to 4K blocks
	uint32_t memory_map_length = (max_blocks / FRAMES_PER_BYTE + FRAME_SIZE - 1) & ~(FRAME_SIZE - 1);
	deinitialise_memory_region((uint32_t)&_kernel_end_physical, memory_map_length);

	printk("Total blocks: 0x%u\n", max_blocks);
	printk("Used blocks: 0x%u\n", used_blocks);
	printk("Free blocks: 0x%u\n", max_blocks - used_blocks);
}
