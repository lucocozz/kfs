#include "memory/memory.h"
#include "utils.h"

uint32_t	kmalloc_internal(uint32_t size, bool align, uint32_t *phys)
{
	uint32_t			address;
	static uint32_t		placement_address = (uint32_t)&_kernel_end;

	if (align == true && (placement_address & 0xFFFFF000)) {
		placement_address &= 0xFFFFF000;
		placement_address += PAGE_SIZE;
	}

	if (phys != NULL)
		*phys = placement_address;

	address = placement_address;
	placement_address += size;

	return (address);
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

uint32_t	kmalloc(uint32_t size)
{
	return (kmalloc_internal(size, false, NULL));
}
