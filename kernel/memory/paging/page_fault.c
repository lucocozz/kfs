#include "memory/memory.h"

void	page_fault_handler(struct cpu_state cpu, struct stack_state stack)
{
	uint32_t faulting_address;

	UNUSED(cpu);
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	printk("Page fault! (%d, %d, %d, %d, %d) at %08p\n", 
		!(stack.error_code & 0x1),
		stack.error_code & PAGE_FLAG_WRITE,
		stack.error_code & PAGE_FLAG_USER,
		stack.error_code & PAGE_FLAG_RESERVED,
		stack.error_code & PAGE_FLAG_GLOBAL,
		faulting_address
	);
}
EXPORT_SYMBOL(page_fault_handler);
