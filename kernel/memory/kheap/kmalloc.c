#include "memory/memory.h"
#include "memory/memory_map.h"
#include "system/utils.h"

uint32_t	g_placement_address = 0x00;

static void *__kbrk(uint32_t size) {
    void *addr = NULL;

    if (size == 0)
        return (NULL);
    else {
        addr = (void *)g_placement_address;
        g_placement_address += size;
		printk("Placement address: %x\n", g_placement_address);
    }
    return (addr);
}

uint32_t	kmalloc_internal(uint32_t size, bool align, uint32_t *phys)
{
	if (align == true && (g_placement_address & 0x00000FFF)) {
		g_placement_address &= 0xFFFFF000;
		g_placement_address += PAGE_SIZE;
	}

	if (phys != NULL)
		*phys = g_placement_address;

	return ((uint32_t)__kbrk(size));
}

uint32_t	kmalloc_a(uint32_t size)
{
	return (kmalloc_internal(size, true, NULL));
}

uint32_t	kmalloc_p(uint32_t size, uint32_t *phys)
{
	return (kmalloc_internal(size, false, phys));
}

uint32_t	kmalloc_ap(uint32_t size, uint32_t *phys)
{
	return (kmalloc_internal(size, true, phys));
}

// uint32_t	kmalloc(uint32_t size)
// {
// 	return (kmalloc_internal(size, false, NULL));
// }
