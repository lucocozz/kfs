#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <stddef.h>
#include <stdint.h>

#include "system/interrupts.h"
#include "system/utils.h"

#include "memory/kmalloc.h"
#include "memory/memory_map.h"
#include "memory/segments.h"

#define CPU_ARCH_BITS	32
#define KERNEL_START	0xC0000000

#define PAGE_SIZE			4096
#define PAGE_DIR_SIZE		1024
#define PAGE_TABLE_SIZE		1024

#define PAGE_INDEX(addr) ((addr) / PAGE_SIZE) % PAGE_TABLE_SIZE
#define PAGE_TABLE_INDEX(addr) ((addr) / PAGE_SIZE) / PAGE_TABLE_SIZE

#define PAGE_FLAG_PRESENT	0x1
#define PAGE_FLAG_WRITE		0x2
#define PAGE_FLAG_USER		0x4
#define PAGE_FLAG_RESERVED	0x8
#define PAGE_FLAG_GLOBAL	0x10
#define PAGE_FLAG_ACCESS	0x20
#define PAGE_FLAG_DIRTY		0x40

#define BITMAP_INDEX(a) (a / CPU_ARCH_BITS)
#define BITMAP_OFFSET(a) (a % CPU_ARCH_BITS)


#define KHEAP_START	0xC0000000 // 3072MB
#define KHEAP_SIZE	0x1000000 // 16MB
#define KHEAP_END	(KHEAP_START + KHEAP_SIZE)
#define NUM_FRAMES	(KHEAP_SIZE / PAGE_SIZE) // 4096
#define FRAMES_SIZE	BITMAP_INDEX(NUM_FRAMES)
#define FRAME_FULL	0xFFFFFFFF

typedef struct page {
	uint32_t	present		: 1;
	uint32_t	rw			: 1;
	uint32_t	user		: 1;
	uint32_t	accessed	: 1;
	uint32_t	dirty		: 1;
	uint32_t	unused		: 7;
	uint32_t	frame		: 20;
} __Packed__ page_t;

typedef struct page_table {
	page_t pages[PAGE_TABLE_SIZE] __Aligned__(PAGE_SIZE);
} page_table_t;

typedef struct page_directory {
	struct {
		page_table_t	*virtual[PAGE_DIR_SIZE];
		uint32_t		physical[PAGE_DIR_SIZE];
	} tables;
	uint32_t		physical_address;
} page_directory_t;


extern uint32_t	g_placement_address;
extern uint32_t	*g_frames;

// extern void enable_paging(uint32_t page_directory);
void	memory_init(void);
void	isr_page_fault(registers_t regs, struct stack_state stack);
// void	alloc_frame(page_t *page, bool is_kernel, bool is_writeable);
// page_t	*gepage_header_t(uint32_t address, page_directory_t *directory, bool make);


static inline int getpagesize(void) {
	return (PAGE_SIZE);
}

static inline uint32_t address_distance(void *ptr1, void *ptr2) {
	if (ptr1 == NULL || ptr2 == NULL)
		return (0);
	return ((uint32_t)ptr2 - (uint32_t)ptr1);
}


#endif