#include "memory/vmm.h"


void	*mmap(size_t size)
{
	size = ALIGN_WITH(size, PAGE_SIZE);
	
	int			num_pages = size / PAGE_SIZE;
	uint32_t	*page = (uint32_t*)g_placement_address;

	for (int i = 0; i < num_pages; ++i)
	{
		alloc_page(get_page(g_placement_address));
		g_placement_address += PAGE_SIZE;
	}
	
	return (page);
}