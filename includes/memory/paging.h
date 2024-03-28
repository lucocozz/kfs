#ifndef KERNEL_MEMORY_PAGING_H
#define KERNEL_MEMORY_PAGING_H

#include <stdbool.h>

#include "memory/vmm.h"


void	enable_paging(void);
bool	switch_page_directory(page_directory_t *directory);
void	flush_tlb_entry(uint32_t v_addr);
void	isr_page_fault(registers_t regs, struct stack_state stack);

#endif
