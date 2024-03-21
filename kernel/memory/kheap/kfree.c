#include "memory/kmalloc.h"

static void	__merge_blocks(page_header_t *page, block_header_t *first, block_header_t *second)
{
	first->size += second->size;
	first->next = second->next;
	if (second->next != NULL)
		second->next->prev = first;
	page->block_count--;
	page->freed_count--;
}

static void	__clean_last_block(block_header_t *block)
{
	block_header_t	*prev = block->prev;
	page_header_t	*page = block->parent;

	if (block->next == NULL) {
		page->used_size -= block->size;
		page->block_count--;
		page->freed_count--;
		if (prev != NULL)
			prev->next = NULL;
	}
}

static void	__block_defragmentation(page_header_t *page, block_header_t *block)
{
	block_header_t	*prev = NULL;
	block_header_t	*next = NULL;

	prev = block->prev;
	if (prev != NULL && prev->allocated == false) {
		__merge_blocks(page, prev, block);
		block = prev;
	}
	next = block->next;
	if (next != NULL && next->allocated == false)
		__merge_blocks(page, block, next);
	__clean_last_block(block);
}

static page_queue_t	*__get_page_queue(page_header_t *page)
{
	if (page->size == TINY_PAGE_SIZE)
		return (&g_heap.tiny);
	else if (page->size == SMALL_PAGE_SIZE)
		return (&g_heap.small);
	else
		return (&g_heap.large);
}

static void	__free_page(page_header_t *page)
{
	page_queue_t *page_queue = __get_page_queue(page);

	if (page_queue->count == 0)
		return;
	page_queue->count--;
	if (page_queue->pages == page)
		page_queue->pages = page->next;

	if (page->prev != NULL)
		page->prev->next = page->next;
	if (page->next != NULL)
		page->next->prev = page->prev;

	// if (munmap(page, page->size) == -1)
	// 	ft_putstr("free(): munmap error\n");
}

void	kfree(void *ptr)
{
	page_header_t	*page;
	block_header_t	*block = BLOCK_HEADER_SHIFT_BACK(ptr);

	if (ptr == NULL)
		return;
	if (block->magic != KMALLOC_MAGIC)
		return;

	// pthread_mutex_lock(&g_heap_mutex);

	page = block->parent;
	block->allocated = false;
	page->freed_count++;
	if (page->freed_count == page->block_count)
		__free_page(page);
	else
		__block_defragmentation(page, block);

	// pthread_mutex_unlock(&g_heap_mutex);
}
