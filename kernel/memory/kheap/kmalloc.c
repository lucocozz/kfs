#include "memory/kmalloc.h"


typedef struct block_index {
	block_header_t	*block;
	page_header_t	*page;
} __Packed__ block_index_t;


static size_t	__page_size_from_block_size(size_t block_size)
{
	if (block_size <= TINY_BLOCK_SIZE_MAX)
		return (TINY_PAGE_SIZE);
	else if (block_size <= SMALL_BLOCK_SIZE_MAX)
		return (SMALL_PAGE_SIZE);
	else
		return (LARGE_PAGE_SIZE(block_size));
}

static page_header_t	*__alloc_page(size_t size)
{
	page_header_t *page;

	//TODO: check memory limit
	page = (page_header_t*)kbrk(size);
	if (page == NULL)
		return (NULL);
	bzero(page, sizeof(page_header_t));
	page->size = size;
	page->used_size = sizeof(page_header_t);
	return (page);
}

static block_header_t	*__find_fitting_block(page_header_t *page, size_t block_size)
{
	block_header_t	*last_block = NULL;
	block_header_t	*block = page->blocks;

	// Create block at start of page if none exists
	if (page->blocks == NULL) {
		page->block_count = 1;
		page->blocks = PAGE_HEADER_SHIFT(page);
		page->blocks->next = NULL;
		page->blocks->prev = NULL;
		page->used_size += block_size;
		return (page->blocks);
	}

	// Search for a freed block
	for (uint i = 0; i < page->block_count; i++) {
		if (block->allocated == false && block_size <= block->size) {
			page->freed_count--;
			return (block);
		}
		last_block = block;
		block = block->next;
	}

	// Add block at end if there is space available
	if (block_size <= page->size - page->used_size) {
		block = BLOCK_SHIFT(last_block, last_block->size);
		block->next = NULL;
		block->prev = last_block;
		last_block->next = block;
		page->used_size += block_size;
		page->block_count++;
		return (block);
	}
	return (NULL);
}

static block_index_t	__find_first_fit(page_queue_t *queue, size_t block_size)
{
	block_header_t	*block = NULL;
	page_header_t	*last_page = NULL;
	page_header_t	*page = queue->pages;

	// Search a page with a avalaible block
	while (page != NULL) {
		if ((block = __find_fitting_block(page, block_size)) != NULL)
			return ((block_index_t){.page = page, .block = block});
		last_page = page;
		page = page->next;
	}

	// Create a new page if none is available
	page = __alloc_page(__page_size_from_block_size(block_size));
	if (page == NULL)
		return ((block_index_t){NULL, NULL});
	if (last_page != NULL) {
		last_page->next = page;
		page->prev = last_page;
	}
	else
		queue->pages = page;
	queue->count++;
	return ((block_index_t){.page = page, .block = __find_fitting_block(page, block_size)});
}

static int	__block_fragmentation(block_header_t *block)
{
	page_header_t	*parent = block->parent;
	block_header_t	*next_block = BLOCK_SHIFT(block, block->size);

	if (address_distance(block->next, next_block) < BLOCK_SIZE(ALIGNMENT))
		return (0);
	next_block->next = block->next;
	block->next->prev = next_block;
	next_block->prev = block;
	next_block->allocated = false;
	next_block->parent = parent;
	next_block->size = block->next - next_block;
	block->next = next_block;
	parent->block_count++;
	parent->freed_count++;
	return (1);
}

static void	*__do_alloc(page_queue_t *queue, size_t block_size)
{
	block_index_t	index;

	index = __find_first_fit(queue, block_size);
	if (index.page == NULL)
		return (NULL);
	index.block->magic = KMALLOC_MAGIC;
	index.block->allocated = true;
	index.block->size = block_size;
	index.block->parent = index.page;
	__block_fragmentation(index.block);
	return (BLOCK_HEADER_SHIFT(index.block));
}

void	*kmalloc(size_t size)
{
	void	*alloc;
	size_t	block_size = BLOCK_SIZE(size);

	if (size == 0)
		return (NULL);

	// pthread_mutex_lock(&g_heap_mutex);

	if (block_size <= TINY_BLOCK_SIZE_MAX)
		alloc = __do_alloc(&g_heap.tiny, block_size);
	else if (block_size <= SMALL_BLOCK_SIZE_MAX)
		alloc = __do_alloc(&g_heap.small, block_size);
	else
		alloc = __do_alloc(&g_heap.large, block_size);
	
	// pthread_mutex_unlock(&g_heap_mutex);

	return (alloc);
}
