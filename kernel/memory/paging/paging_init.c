#include "symbol_table.h"
#include "string.h"
#include "memory/memory.h"

uint32_t			*g_frames = NULL;
page_directory_t	*g_kernel_directory = NULL;
page_directory_t	*g_current_directory = NULL;

static void	__init_frames(void)
{
	g_frames = (uint32_t*)kmalloc(FRAMES_SIZE);
	bzero(g_frames, FRAMES_SIZE);
}

static void	__init_directory(void)
{
	g_kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	bzero(g_kernel_directory->tables.virtual, sizeof(page_table_t*) * PAGE_DIR_SIZE);
	memset32(g_kernel_directory->tables.physical, 0, PAGE_DIR_SIZE);
	g_current_directory = g_kernel_directory;
}

static void	__switch_page_directory(page_directory_t *directory)
{
	// return ;
	g_current_directory = directory;
	printk("%p\n", &directory->tables.physical);
	asm volatile("mov %0, %%cr3" :: "r" (&directory->tables.physical));
	// uint32_t cr0;
	// asm volatile("mov %%cr0, %0" : "=r" (cr0));
	// cr0 |= 0x80000000;
	// asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

void paging_init(void)
{
	__init_frames();
	__init_directory();

	for (uint32_t i = KHEAP_START; i < KHEAP_END; i += PAGE_SIZE)
		alloc_frame(get_page(i, g_kernel_directory, true), false, false);

	// PAUSE_RUNTIME;
	__switch_page_directory(g_kernel_directory);
	// enable_paging((uint32_t)g_kernel_directory->tables.physical);
}
EXPORT_SYMBOL(paging_init);
