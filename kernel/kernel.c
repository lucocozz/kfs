#include "kernel.h"

// void pmm_tests(void)
// {
//     /*
//      * Test allocations and frees
//      */
// 	uint32_t highest_allocated_address = 0;
// 	uint32_t lowest_allocated_address = 0xFFFFFFFF;

//     printk("PMM: Testing memory allocations...\n");
//     for(uint32_t i = 0; i < nb_frames * 2; i++)
//     {
//         uint32_t* mem_addr = kmalloc();
// 		// detect highest address allocated
// 		if ((uint32_t)mem_addr > highest_allocated_address)
// 			highest_allocated_address = (uint32_t)mem_addr;
// 		if ((uint32_t)mem_addr < lowest_allocated_address)
// 			lowest_allocated_address = (uint32_t)mem_addr;
//         int res = kfree(mem_addr);
//         if(res != 0)
//             panic("error freeing memory!");
//     }
// 	printk("Highest address allocated: %x\n", highest_allocated_address);
// 	printk("Lowest address allocated: %x\n", lowest_allocated_address);
//     printk("Passed.\n");
// }

static void	__init_kernel(multiboot_info_t *boot_info)
{
	term_init();
	gdt_init();
	idt_init();

	// Check flags
	init_memory_map(boot_info);
	get_memory_map();

	    uint32_t nb_of_mmap_entries = g_boot_info->mmap_length / sizeof(multiboot_mmap_entry_t);
    multiboot_mmap_entry_t *mmap_entry = (multiboot_mmap_entry_t*)g_boot_info->mmap_addr + nb_of_mmap_entries - 1;

    uint32_t total_memory = mmap_entry->addr_low + mmap_entry->len_low;

    printk("Total memory: %d \n", total_memory);

    initialise_memory_manager((uint32_t)&_kernel_end_physical, total_memory);

	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t))
	{
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);

		if(entry->type == 1) // && entry->len_low > main_memory_length)
            initialise_memory_region(entry->addr_low, entry->len_low);
	}

	// pmm_tests();
}

void	kernel_main(uint32_t magic, multiboot_info_t *boot_info, uint32_t *stack_top)
{
	UNUSED(stack_top);
	assert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
	__init_kernel(boot_info);
	shell();
}
EXPORT_SYMBOL(kernel_main);
