#include "memory.h"

static size_t	__print_blocks(page_header_t *page)
{
	size_t			total = 0;
	block_header_t	*block = page->blocks;

	for (uint i = 0; i < page->block_count; ++i)
	{
		size_t block_size = block->size - sizeof(block_header_t);
		printk("  %p - %p : ", BLOCK_HEADER_SHIFT(block), BLOCK_SHIFT(block, block->size));
		if (block->allocated == true) {
			printk("%d bytes\n", block_size);
			total += block_size;
		}
		else
			printk("freed\n");
		block = block->next;
	}
	return (total);
}

static size_t	__print_pages(page_queue_t *queue, const char *type)
{
	size_t			total = 0;
	page_header_t	*page = queue->pages;

	for (uint i = 0; i < queue->count; ++i)
	{
		printk("%s : %p\n", type, page);
		total += __print_blocks(page);
		page = page->next;
	}
	return (total);
}

void	show_alloc_mem_freed(void)
{
	size_t	total = 0;

	// pthread_mutex_lock(&g_heap_mutex);
	total += __print_pages(&g_heap.tiny, "TINY");
	total += __print_pages(&g_heap.small, "SMALL");
	total += __print_pages(&g_heap.large, "LARGE");
	printk("Total : %d bytes\n", total);
	// pthread_mutex_unlock(&g_heap_mutex);
}
