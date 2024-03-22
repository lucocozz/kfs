#ifndef KERNEL_MEMORY_KMALLOC_H
#define KERNEL_MEMORY_KMALLOC_H

#include "system/utils.h"
#include "memory.h"
#include "string.h"

#define KMALLOC_MAGIC	0xdeadbeef
#define ALIGNMENT		8
#define ALIGN(size)		(((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define BLOCK_SIZE(size)	(ALIGN(size) + sizeof(block_header_t))

// BLOCK
#define HEADER_BLOCK_SIZE				sizeof(block_header_t)
#define BLOCK_HEADER_SHIFT(block)		(void*)((uint32_t)block + sizeof(block_header_t))
#define BLOCK_HEADER_SHIFT_BACK(ptr)	((block_header_t*)((uint32_t)ptr - sizeof(block_header_t)))
#define BLOCK_SHIFT(block, size)		(block_header_t*)((uint32_t)block + size)

// PAGE
#define HEADER_PAGE_SIZE			sizeof(page_header_t)
#define PAGE_HEADER_SHIFT(page)		(block_header_t*)((uint32_t)page + sizeof(page_header_t))
#define PAGE_HEADER_SHIFT_BACK(ptr)	((uint32_t)ptr - sizeof(page_header_t))


#define MIN_PAGE_BLOCKS 128

// TINY
#define TINY_BLOCK_SIZE_MAX	256
#define TINY_BLOCK_SIZE		BLOCK_SIZE(TINY_BLOCK_SIZE_MAX)
#define TINY_PAGE_SIZE		(((MIN_PAGE_BLOCKS * TINY_BLOCK_SIZE + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())

// SMALL
#define SMALL_BLOCK_SIZE_MAX	2048
#define SMALL_BLOCK_SIZE		BLOCK_SIZE(SMALL_BLOCK_SIZE_MAX)
#define SMALL_PAGE_SIZE			(((MIN_PAGE_BLOCKS * SMALL_BLOCK_SIZE + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())

// LARGE
#define LARGE_PAGE_SIZE(size)	(((BLOCK_SIZE(size) + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())

#define INITIALIZE_HEAP {.tiny = {.count = 0, .pages = NULL, }, .small = {.count = 0, .pages = NULL}, .large = {.count = 0, .pages = NULL}}


typedef struct block_header {
	uint32_t			magic;
	size_t				size;
	bool				allocated;
	struct page_header	*parent;
	struct block_header	*next;
	struct block_header	*prev;
} __Aligned__(ALIGNMENT) block_header_t;

typedef struct page_header {
	size_t				size;
	size_t				used_size;
	uint				block_count;
	uint				freed_count;
	block_header_t		*blocks;
	struct page_header	*next;
	struct page_header	*prev;
} __Aligned__(ALIGNMENT) page_header_t;

typedef struct page_queue {
	size_t			count;
	page_header_t	*pages;
} __Aligned__(ALIGNMENT) page_queue_t;

typedef struct heap {
	page_queue_t	tiny;
	page_queue_t	small;
	page_queue_t	large;
} __Aligned__(ALIGNMENT) heap_t;

extern heap_t g_heap;

uint32_t	kbrk(uint32_t size);
void		kfree(void *ptr);
void		*kmalloc(size_t size);
void		*krealloc(void *ptr, size_t size);
void		*kcalloc(size_t nmemb, size_t size);


void	show_alloc_mem(void);
void	show_alloc_mem_hex(void);
void	show_alloc_mem_freed(void);
void	show_page_num(void);
void	print_memory(void *address, uint size);



#endif
