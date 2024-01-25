#ifndef KERNEL_MEMORY_PAGING_H
#define KERNEL_MEMORY_PAGING_H

#include <stddef.h>
#include <stdint.h>

#include "interrupt/interrupts.h"
#include "utils.h"

#define CPU_ARCH_BITS	32
#define KERNEL_START	0xC0000000

#define PAGE_SIZE			4096
#define PAGE_DIR_SIZE		1024
#define PAGE_TABLE_SIZE		1024

#define PAGE_FLAG_PRESENT	0x1
#define PAGE_FLAG_WRITE		0x2

#define INDEX_FROM_BIT(a) (a / CPU_ARCH_BITS)
#define OFFSET_FROM_BIT(a) (a % CPU_ARCH_BITS)

#define MEM_END_PAGE	0x1000000 // 16MB


typedef struct page {
	uint32_t	present		: 1;
	uint32_t	rw			: 1;
	uint32_t	user		: 1;
	uint32_t	accessed	: 1;
	uint32_t	dirty		: 1;
	uint32_t	unused		: 7;
	uint32_t	frame		: 20;
} __packed page_t;

typedef struct page_table {
	page_t pages[PAGE_TABLE_SIZE] __aligned(PAGE_SIZE);
} page_table_t;

typedef struct page_directory {
	struct {
		page_table_t	*virtual[PAGE_DIR_SIZE];
		uint32_t		physical[PAGE_DIR_SIZE];
	} tables;
	uint32_t		physical_address;
} page_directory_t;


extern uint32_t	_kernel_end;


void	paging_init(void);
void	page_fault_handler(struct cpu_state cpu, struct stack_state stack);


/* MEMORY/KHEAP/KMALLOC.C */
uint32_t	kmalloc_internal(uint32_t size, bool align, uint32_t *phys);
uint32_t	kmalloc_a(uint32_t size);
uint32_t	kmalloc_p(uint32_t size, uint32_t *phys);
uint32_t	kmalloc_ap(uint32_t size, uint32_t *phys);
uint32_t	kmalloc(uint32_t size);

#endif