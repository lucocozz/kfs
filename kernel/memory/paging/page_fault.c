#include "../includes/memory.h"

void	isr_page_fault(registers_t regs, struct stack_state stack)
{
	uint32_t faulting_address;

	UNUSED(regs);
	ASM("mov %%cr2, %0" : "=r" (faulting_address));

	panic("Page fault! (%d, %d, %d, %d, %d) at %08p\n", 
		!(stack.error_code & PTE_PRESENT),		// when set, the page fault was caused by a non-present page
		stack.error_code & PTE_READ_WRITE,		// when set, the page fault was caused by a write
		stack.error_code & PTE_USER,			// when set, the page fault was caused while CPL = 3
		stack.error_code & PTE_WRITETHROUGH,
		stack.error_code & PTE_NOT_CACHEABLE,
		faulting_address
	);
}
EXPORT_SYMBOL(isr_page_fault);
