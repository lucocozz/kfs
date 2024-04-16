#include "memory/vmalloc.h"

static int	__block_defragmentation(block_header_t *block, size_t size)
{
	block_header_t	*next = block->next;
	page_header_t	*page = block->parent;

	if (next != NULL && next->allocated == false && block->size + next->size >= size)
	{
		block->size += next->size;
		block->next = next->next;
		page->block_count--;
		page->freed_count--;
		return (true);
	}
	return (false);
}

static void	__clean_fragmentation(block_header_t *block)
{
	if (block != NULL && block->next != NULL && block->next->allocated == false)
	{
		page_header_t	*page = block->parent;
		block_header_t	*next = block->next;

		block->size += next->size;
		block->next = next->next;
		if (next->next != NULL)
			next->next->prev = block;
		page->block_count--;
		page->freed_count--;
	}
}

static int __block_fragmentation(block_header_t *block, size_t size)
{
	block_header_t	*fragment;
	page_header_t	*page = block->parent;

	if (address_distance(block, block->next) - size >= BLOCK_SIZE(ALIGNMENT))
	{
		if (block->next != NULL)
		{
			fragment = BLOCK_SHIFT(block, size);
			fragment->allocated = false;
			fragment->parent = page;
			fragment->size = block->size - size;
			fragment->next = block->next;
			fragment->prev = block;
			fragment->magic = VMALLOC_MAGIC;
			block->next = fragment;
			page->block_count++;
			page->freed_count++;
		}
		else
			page->used_size -= (block->size - size);
		block->size = size;
		__clean_fragmentation(block->next);
		return (true);
	}
	return (false);
}

static int	__check_defragmentation(block_header_t *block, size_t size)
{
	if (size == block->size)
		return (true);
	else if (size > block->size)
		return (__block_defragmentation(block, size));
	else
		return (__block_fragmentation(block, size));
}

void	*vrealloc(void *ptr, size_t size)
{
	if (size == 0) {
		if (ptr != NULL)
			vfree(ptr);
		return (NULL);
	}
	
	if (ptr == NULL)
		return (vmalloc(size));

	block_header_t	*block = BLOCK_HEADER_SHIFT_BACK(ptr);
	if (block->magic != VMALLOC_MAGIC)
		return (NULL);

	// pthread_mutex_lock(&g_heap_mutex);
	int	is_fragmented = __check_defragmentation(block, BLOCK_SIZE(size));
	// pthread_mutex_unlock(&g_heap_mutex);
	
	if (is_fragmented == true)
		return (ptr);

	void *new = vmalloc(size);
	if (new == NULL)
		return (NULL);

	// pthread_mutex_lock(&g_heap_mutex);
	// strcpy(new, ptr);
	memcpy(new, ptr, block->size);
	// pthread_mutex_unlock(&g_heap_mutex);

	vfree(ptr);
	return (new);
}
