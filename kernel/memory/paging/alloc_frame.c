#include "memory/memory.h"

static void	__set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / PAGE_SIZE;
	uint32_t index = BITMAP_INDEX(frame);
	uint32_t offset = BITMAP_OFFSET(frame);

	g_frames[index] |= (0x1 << offset);
}

static uint32_t	__get_first_free_frame(void)
{
	uint32_t len = FRAMES_SIZE;

	for (uint32_t i = 0; i < len; ++i)
	{
		if (g_frames[i] == FRAME_FULL)
			continue ;
		for (uint8_t bit = 0; bit < CPU_ARCH_BITS; ++bit)
		{
			uint32_t tested_bit = 0x1 << bit;
			if (!(g_frames[i] & tested_bit))
				return (i * CPU_ARCH_BITS + bit);
		}
	}
	return (-1);
}

void	alloc_frame(page_t *page, bool is_kernel, bool is_writeable)
{
	if (page == NULL || page->frame != 0)
		return ;

	uint32_t index = __get_first_free_frame();
	if (index == (uint32_t)-1) {
		printk(KERN_CRIT "No free frames!\n");
		while (1);
		// ! implement paging out to disk
	}

	__set_frame(index * PAGE_SIZE);
	page->present = 1;
	page->rw = (is_writeable == true) ? 1 : 0;
	page->user = (is_kernel == true) ? 0 : 1;
	page->frame = index;
}
EXPORT_SYMBOL(alloc_frame);
