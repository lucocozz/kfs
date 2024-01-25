#include "symbol_table.h"
#include "string.h"
#include "memory/memory.h"

static uint32_t			*g_frames_bitmap;
static uint32_t			g_num_frames;
static page_directory_t	*g_kernel_directory;
static page_directory_t	*g_current_directory;

void	page_fault_handler(struct cpu_state cpu, struct stack_state stack)
{
	uint32_t faulting_address;

	UNUSED(cpu);
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	bool present = !(stack.error_code & 0x1);
	bool rw = stack.error_code & 0x2;
	bool us = stack.error_code & 0x4;
	bool reserved = stack.error_code & 0x8;
	bool id = stack.error_code & 0x10;

	printk("Page fault! (%d, %d, %d, %d, %d) at %p\n", present, rw, us, reserved, id, faulting_address);
}
EXPORT_SYMBOL(page_fault_handler);


static void	__set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / PAGE_SIZE;
	uint32_t index = INDEX_FROM_BIT(frame);
	uint32_t offset = OFFSET_FROM_BIT(frame);

	g_frames_bitmap[index] |= (0x1 << offset);
}

// static void	__clear_frame(uint32_t frame_addr)
// {
// 	uint32_t frame = frame_addr / PAGE_SIZE;
// 	uint32_t index = INDEX_FROM_BIT(frame);
// 	uint32_t offset = OFFSET_FROM_BIT(frame);

// 	g_frames_bitmap[index] &= ~(0x1 << offset);
// }

// static uint32_t	__test_frame(uint32_t frame_addr)
// {
// 	uint32_t frame = frame_addr / PAGE_SIZE;
// 	uint32_t index = INDEX_FROM_BIT(frame);
// 	uint32_t offset = OFFSET_FROM_BIT(frame);

// 	return (g_frames_bitmap[index] & (0x1 << offset));
// }

static int32_t	__first_free_frame(void)
{
	uint32_t len = INDEX_FROM_BIT(g_num_frames);

	for (uint32_t i = 0; i < len; ++i)
	{
		if (g_frames_bitmap[i] != 0xFFFFFFFF)
		{
			for (uint8_t bit = 0; bit < CPU_ARCH_BITS; ++bit)
			{
				uint32_t tested_bit = 0x1 << bit;

				if (g_frames_bitmap[i] & tested_bit)
					return (i * CPU_ARCH_BITS + bit); 
			}
		}
	}
	return (-1);
}

void	__alloc_frame(page_t *page, bool is_kernel, bool is_writeable)
{
	if (page->frame != 0)
		return ;

	int32_t index = __first_free_frame();
	if (index == -1) {
		printk(KERN_CRIT "No free frames!\n");
		return ;
		// ! implement paging out to disk
	}

	__set_frame(index * PAGE_SIZE);
	page->present = 1;
	page->rw = (is_writeable == true) ? 1 : 0;
	page->user = (is_kernel == true) ? 0 : 1;
	page->frame = index;
}

page_t	*get_page(uint32_t address, page_directory_t *directory, bool make)
{
	address /= PAGE_SIZE; // Transform address to page index

	uint32_t table_index = address / PAGE_TABLE_SIZE;
	uint32_t page_index = address % PAGE_TABLE_SIZE;

	if (directory->tables.virtual[table_index] != NULL)
		return (&directory->tables.virtual[table_index]->pages[page_index]);
	else if (make == true)
	{
		uint32_t physical_address;

		directory->tables.virtual[table_index] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &physical_address);
		directory->tables.physical[table_index] = physical_address | 0x7;
		return (&directory->tables.virtual[table_index]->pages[page_index]);
	}
	return (NULL);
}

static void	__switch_page_directory(page_directory_t *directory)
{
	g_current_directory = directory;
	asm volatile("mov %0, %%cr3" : : "r" (&directory->physical_address));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

void paging_init(void)
{
	uint32_t kernel_end_page = (uint32_t)&_kernel_end / PAGE_SIZE;

	g_num_frames = MEM_END_PAGE / PAGE_SIZE;
	g_frames_bitmap = (uint32_t*)kmalloc(INDEX_FROM_BIT(g_num_frames));
	bzero(g_frames_bitmap, INDEX_FROM_BIT(g_num_frames));

	g_kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	bzero(g_kernel_directory->tables.virtual, PAGE_DIR_SIZE * sizeof(page_table_t *));
	bzero(g_kernel_directory->tables.physical, PAGE_DIR_SIZE * sizeof(uint32_t));
	g_current_directory = g_kernel_directory;

	for (uint32_t i = 0; i < kernel_end_page; ++i)
		__alloc_frame(get_page(i * PAGE_SIZE, g_kernel_directory, true), true, false);

	__switch_page_directory(g_kernel_directory);
}
EXPORT_SYMBOL(paging_init);
