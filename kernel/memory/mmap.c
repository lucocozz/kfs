#include "memory/vmm.h"


static void	__fragment_free_page(page_free_t *page, size_t count)
{
	page_free_t	*new_page = (page_free_t*)((uint32_t)page + (count * PAGE_SIZE));

	new_page->next = page->next;
	new_page->count = page->count - count;

	page->next = new_page;
	page->count = count;
}

static void __remove_page_from_free_list(page_free_t *page, page_free_t *prev)
{
	if (prev != NULL)
		prev->next = page->next;
	else
		g_free_list = page->next;
	page->next = NULL;
	page->count = 0;
}

static uint32_t	*__find_best_free_page(size_t count)
{
	page_free_t	*best = NULL;
	page_free_t	*prev = NULL;
	
	if (g_free_list == NULL)
		return (NULL);

	for (page_free_t *page = g_free_list; page != NULL; page = page->next)
	{
		if (page->count >= count && (best == NULL || page->count < best->count))
		{
			best = page;
			if (prev != NULL)
				prev->next = page->next;
			else
				g_free_list = page->next;
		}
		prev = page;
	}
	if (best == NULL)
		return (NULL);

	if (best->count > count)
		__fragment_free_page(best, count);

	__remove_page_from_free_list(best, prev);

	return ((uint32_t *)best);
}

static uint32_t *__request_pages(size_t count)
{
	uint32_t	*page = (uint32_t *)g_placement_address;

	for (size_t i = 0; i < count; ++i) {
		vmm_alloc_page(vmm_get_page(g_placement_address));
		g_placement_address += PAGE_SIZE;
	}

	return (page);
}

void	*mmap(size_t size)
{
	size = ALIGN_WITH(size, PAGE_SIZE);
	
	int			pages_count = size / PAGE_SIZE;
	uint32_t	*page = __find_best_free_page(pages_count);

	if (page == NULL)
		page = __request_pages(pages_count);
	
	return (page);
}