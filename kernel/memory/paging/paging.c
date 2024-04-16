#include "../includes/memory.h"

// Set the current page directory
bool switch_page_directory(uint32_t *directory)
{
	if (directory == NULL)
		return (false);
	g_current_directory = directory;

	ASM("movl %0, %%cr3":: "r"(g_current_directory));
	return (true);
}

// Flush a single page in TLB
void flush_tlb_entry(uint32_t v_addr)
{
	ASM("cli; invlpg (%0); sti":: "r"(v_addr) );
}


void	enable_paging(void)
{
	ASM("movl %cr0, %eax; orl $0x80000001, %eax; movl %eax, %cr0");
}