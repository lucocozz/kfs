#include "memory/vmm.h"

static void	__defragment_free_page(page_free_t *page, page_free_t *next)
{
	if (page == NULL || next == NULL)
		return ;
	if ((uint32_t)page + (page->count * PAGE_SIZE) != (uint32_t)next)
		return ;
	page->count += next->count;
	page->next = next->next;
	next->next = NULL;
	next->count = 0;
}

static void	__release_memory_at_heap_end(page_free_t *prev, page_free_t *page)
{
	if ((uint32_t)page + (page->count * PAGE_SIZE) != g_placement_address)
		return ;
	g_placement_address = (uint32_t)page;
	if (prev != NULL)
		prev->next = NULL;
	else
		g_free_list = NULL;
	for (size_t i = 0; i < page->count; ++i)
		vmm_unmap_page((uint32_t *)page + (i * PAGE_SIZE));
}

static void	__insert_page_to_free_list(uint32_t addr, size_t count)
{
	page_free_t	*page = (page_free_t *)addr;
	page_free_t	*prev = NULL;
	page_free_t	*current = g_free_list;

	page->next = NULL;
	page->count = count;

	while (current != NULL && page > current) {
		prev = current;
		current = current->next;
	}

	if (prev != NULL)
		prev->next = page;
	else
		g_free_list = page;

	page->next = current;

	if (page->next == NULL)
		__release_memory_at_heap_end(prev, page);
	else {
		__defragment_free_page(page, page->next);
		__defragment_free_page(prev, page);
	}
}

int	munmap(void *addr, size_t size)
{
	size = ALIGN_WITH(size, PAGE_SIZE);
	int	pages_count = size / PAGE_SIZE;

	__insert_page_to_free_list((uint32_t)addr, pages_count);
	return (0);
}
EXPORT_SYMBOL(munmap);
