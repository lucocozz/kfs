#include "../includes/memory.h"
#include "system/utils.h"

static void __align_memory(void)
{
	if (g_placement_address & 0xFFFFF000) {
		g_placement_address &= 0xFFFFF000;
		g_placement_address += PAGE_SIZE;
	}
}

uint32_t	kbrk(uint32_t size)
{
	__align_memory();

	uint32_t address = g_placement_address;
	g_placement_address += size;

	return (address);
}
