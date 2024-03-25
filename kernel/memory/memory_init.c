#include "../includes/memory.h"
#include "system/utils.h"
#include "symbol_table.h"

uint32_t	g_placement_address = 0;
heap_t		g_heap = INITIALIZE_HEAP;

uint32_t	*g_frames = NULL;
uint32_t	g_max_frames = 0;
uint32_t	g_used_frames = 0;


static void	__print_header(uint32_t total_memory)
{
	printk("--------------------\n");
	printk("Physical Memory map\n");
	printk("--------------------\n");

	printk("Max memory size in bytes (for a 32 bits system): 0x%X \n", total_memory);
	// this is the nb frames for the full 32 bits address space, we're mapping 4GB even if we have less memory
	// printk("Total 4K frames: 0x%x\n", total_memory * 1024 / FRAME_SIZE); //! OVERFLOW HERE
	printk("Total 4K frames: 0x%x\n", total_memory / FRAME_SIZE); //? CORRECTED (result dont change, but the calculation is correct)
}

static void	__print_footer(void)
{
	printk("Total frames : %d\n", g_max_frames);
	printk("Used frames :  %d\n", g_used_frames);
	printk("Free frames :  %d\n", g_max_frames - g_used_frames);
}

void	memory_init(void)
{
	
	// uint32_t nb_of_mmap_entries = g_boot_info->mmap_length / sizeof(multiboot_mmap_entry_t);
	// multiboot_mmap_entry_t *mmap_entry = (multiboot_mmap_entry_t*)g_boot_info->mmap_addr + sizeof(multiboot_mmap_entry_t) * (nb_of_mmap_entries);
	// uint32_t total_memory = mmap_entry->addr_low + mmap_entry->len_low - 1;
	uint32_t total_memory = MAX_MEMORY_SIZE; // 4GB address space for 32 bits = 0xFFFFFFFF

	__print_header(total_memory);
	
	initialise_memory_manager(g_memory_map.kernel_physical.end, total_memory);
	
	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);

		if (entry->type == MULTIBOOT_MEMORY_AVAILABLE)
			initialise_memory_region(entry->addr_low, entry->len_low);
	}
	
	// set kernel memory as used and align it to 4K frames above the kernel
	uint32_t kernel_memory_length = ALIGN_WITH(g_memory_map.kernel_physical.length, FRAME_SIZE);
	deinitialise_memory_region(g_memory_map.kernel_physical.start, kernel_memory_length);

	// reserve the memory map and align it to 4K frames
	uint32_t memory_map_length = ALIGN_WITH(g_max_frames / FRAMES_PER_BYTE, FRAME_SIZE);
	deinitialise_memory_region(g_memory_map.kernel_physical.end, memory_map_length);
	g_placement_address = g_memory_map.kernel_physical.end + memory_map_length;

	__print_footer();
}
