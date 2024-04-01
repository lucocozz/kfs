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

static void	__insert_page_to_free_list(uint32_t addr, size_t count)
{
	page_free_t	*page = (page_free_t *)addr;
	page_free_t	*prev = NULL;
	page_free_t	*current = g_free_list;

	if (current == NULL)
	{
		g_free_list = page;
		page->next = NULL;
		page->count = count;
		return ;
	}

	while (current != NULL && page >= current)
	{
		prev = current;
		current = current->next;
	}

	page->next = current;
	page->count = count;

	if (prev != NULL)
		prev->next = page;
	else
		g_free_list = page;

	__defragment_free_page(prev, page);
	__defragment_free_page(page, page->next);
}

int	munmap(void *addr, size_t size)
{
	size = ALIGN_WITH(size, PAGE_SIZE);
	int	pages_count = size / PAGE_SIZE;

	__insert_page_to_free_list((uint32_t)addr, pages_count);
	// for (int i = 0; i < pages_count; ++i)
		// vmm_free_page(vmm_get_page((uint32_t)addr + (i * PAGE_SIZE)));
	return (0);
}