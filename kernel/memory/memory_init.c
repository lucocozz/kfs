#include "../includes/memory.h"
#include "system/utils.h"
#include "symbol_table.h"

uint32_t	g_placement_address = 0;
heap_t		g_heap = INITIALIZE_HEAP;

page_free_t	*g_free_list = NULL;

uint32_t	*g_memory_map = NULL;
uint32_t	g_max_frames = 0;
uint32_t	g_used_frames = 0;


void	memory_init(void)
{
	uint32_t total_memory = MAX_MEMORY_SIZE; // 4GB address space for 32 bits = 0xFFFFFFFF

	pmm_init(g_memory_sections.kernel_virtual.end, total_memory);
	
	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);

		if (entry->type == MULTIBOOT_MEMORY_AVAILABLE)
			pmm_unmap_region(entry->addr_low, entry->len_low);
	}
	
	uint32_t kernel_memory_length = ALIGN_WITH(g_memory_sections.kernel_physical.length, FRAME_SIZE);
	pmm_map_region(g_memory_sections.kernel_physical.start, kernel_memory_length);

	uint32_t memory_map_length = ALIGN_WITH(BITMAP_SIZE(g_max_frames) * sizeof(uint32_t), FRAME_SIZE);
	pmm_map_region(g_memory_sections.kernel_physical.end, memory_map_length);

	g_placement_address = g_memory_sections.kernel_virtual.end + memory_map_length;

	if (vmm_init() == ERR_OUT_OF_MEMORY)
		panic("Failed to initialise the virtual memory manager");
}
	