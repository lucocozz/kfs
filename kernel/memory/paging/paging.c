#include "symbol_table.h"
#include "string.h"
#include "memory/memory.h"

static uint32_t			*g_frames = NULL;
static page_directory_t	*g_kernel_directory = NULL;
static page_directory_t	*g_current_directory = NULL;
extern uint32_t			g_placement_address;

void	page_fault_handler(struct cpu_state cpu, struct stack_state stack)
{
	uint32_t faulting_address;

	UNUSED(cpu);
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	bool present = !(stack.error_code & 0x1);
	bool read_write = stack.error_code & PAGE_FLAG_WRITE;
	bool user = stack.error_code & PAGE_FLAG_USER;
	bool reserved = stack.error_code & PAGE_FLAG_RESERVED;
	bool id = stack.error_code & PAGE_FLAG_GLOBAL;

	printk("Page fault! (%d, %d, %d, %d, %d) at %p\n", present, read_write, user, reserved, id, faulting_address);
}
EXPORT_SYMBOL(page_fault_handler);


static void	__set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / PAGE_SIZE;
	uint32_t index = BITMAP_INDEX(frame);
	uint32_t offset = BITMAP_OFFSET(frame);

	g_frames[index] |= (0x1 << offset);
}

// static void	__clear_frame(uint32_t frame_addr)
// {
// 	uint32_t frame = frame_addr / PAGE_SIZE;
// 	uint32_t index = BITMAP_INDEX(frame);
// 	uint32_t offset = BITMAP_OFFSET(frame);

// 	g_frames[index] &= ~(0x1 << offset);
// }

// static uint32_t	__test_frame(uint32_t frame_addr)
// {
// 	uint32_t frame = frame_addr / PAGE_SIZE;
// 	uint32_t index = BITMAP_INDEX(frame);
// 	uint32_t offset = BITMAP_OFFSET(frame);

// 	return (g_frames[index] & (0x1 << offset));
// }

static uint32_t	__get_first_free_frame(void)
{
	uint32_t len = FRAMES_SIZE;
	static uint8_t called_frame[FRAMES_SIZE] = {0};

	for (uint32_t i = 0; i < len; ++i)
	{
		if (g_frames[i] == FRAME_FULL) {
			continue ;
		}
		for (uint8_t bit = 0; bit < CPU_ARCH_BITS; ++bit)
		{
			uint32_t tested_bit = 0x1 << bit;
			if (!(g_frames[i] & tested_bit)) {
				called_frame[i] += 1;
				return (i * CPU_ARCH_BITS + bit);
			}
		}
	}
	return (-1);
}

void	__alloc_frame(page_t *page, bool is_kernel, bool is_writeable)
{
	if (page == NULL || page->frame != 0)
		return ;

	uint32_t index = __get_first_free_frame();
	if (index == (uint32_t)-1) {
		printk(KERN_CRIT "No free frames!\n");
		// while (1);
		// ! implement paging out to disk
	}

	__set_frame(index * PAGE_SIZE);
	page->present = 1;
	page->rw = (is_writeable == true) ? 1 : 0;
	page->user = (is_kernel == true) ? 0 : 1;
	page->frame = index;
}

page_t	*__get_page(uint32_t address, page_directory_t *directory, bool make)
{
	uint32_t table_index = PAGE_TABLE_INDEX(address);
	uint32_t page_index = PAGE_INDEX(address);

	if (directory->tables.virtual[table_index] != NULL)
		return (&directory->tables.virtual[table_index]->pages[page_index]);
	else if (make == true)
	{
		uint32_t physical_address;

		directory->tables.virtual[table_index] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &physical_address);
		bzero(directory->tables.virtual[table_index]->pages, sizeof(page_table_t));
		directory->tables.physical[table_index] = physical_address | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE | PAGE_FLAG_USER;
		return (&directory->tables.virtual[table_index]->pages[page_index]);
	}
	return (NULL);
}

static void	__switch_page_directory(page_directory_t *directory)
{
	g_current_directory = directory;
	asm volatile("mov %0, %%cr3" : : "r" (&directory->tables.physical));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0" : : "r" (cr0));
}

void paging_init(void)
{
	printk("placement address: 0x%x\n", g_placement_address);

	printk("size: %d\n", FRAMES_SIZE);
	g_frames = (uint32_t*)kmalloc(FRAMES_SIZE);
	bzero(g_frames, FRAMES_SIZE);

	g_kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	bzero(g_kernel_directory->tables.virtual, sizeof(page_table_t*) * PAGE_DIR_SIZE);
	memset32(g_kernel_directory->tables.physical, 0, PAGE_DIR_SIZE);
	g_current_directory = g_kernel_directory;

	for (uint32_t i = KHEAP_START; i < KHEAP_END; i += PAGE_SIZE)
		__get_page(i, g_kernel_directory, true);

	for (uint32_t i = 0; i < g_placement_address + PAGE_SIZE; i += PAGE_SIZE)
		__alloc_frame(__get_page(i, g_kernel_directory, true), false, false);
	
	for (uint32_t i = KHEAP_START; i < KHEAP_END; i += PAGE_SIZE)
		__alloc_frame(__get_page(i, g_kernel_directory, true), false, false);
	
	for (uint16_t i = 0; i < 0xFFFF; ++i)
		printk(KERN_INFO "Paging initialized\n");

	__switch_page_directory(g_kernel_directory);
}
EXPORT_SYMBOL(paging_init);
