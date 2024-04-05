#include "../includes/memory.h"

// Set the current page directory
bool switch_page_directory(page_directory_t *directory)
{
	if (directory == NULL)
		return (false);

	// print cr3 register
	// uint32_t cr3;
	// ASM("movl %%cr3, %0": "=r"(cr3));
	// printk("cr3: %x\n", cr3);

	// // print current directory
	// printk("current directory: %x\n", g_current_directory);

	g_current_directory = directory;
	// // PRINT sdata & edata
	// printk("sdata: %x\n", &_sdata);
	// printk("edata: %x\n", &_edata);
	// // print new directory
	// printk("new directory: %x\n", g_current_directory);

	// claer ps bit in cr4 register
	// int ps_bit = ~0x00000010;
	// __asm__ __volatile__("movl %%cr4, %%eax; andl %0, %%eax; movl %%eax, %%cr4":: "r"(ps_bit));
	// panic("switch_page_directory");
	ASM("movl %%eax, %%cr3":: "a"(g_current_directory));
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