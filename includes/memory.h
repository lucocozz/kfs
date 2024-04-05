#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <stddef.h>
#include <stdint.h>
#include "string.h"

#include "system/interrupts.h"
#include "system/utils.h"

#include "memory/vmalloc.h"
#include "memory/memory_map.h"
#include "memory/segments.h"
#include "memory/paging.h"
#include "memory/pmm.h"
#include "memory/vmm.h"

#ifdef __HIGH_KERNEL__
#define KERNEL_START 0xC0000000
#else
#define KERNEL_START 0x00000000
#endif

void	isr_page_fault(registers_t regs, struct stack_state stack);

static inline int getpagesize(void) {
	return (PAGE_SIZE);
}

static inline uint32_t address_distance(void *ptr1, void *ptr2) {
	if (ptr1 == NULL || ptr2 == NULL)
		return (0);
	return ((uint32_t)ptr2 - (uint32_t)ptr1);
}

void	memory_init(void);

#endif