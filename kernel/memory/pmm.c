#include "../includes/memory.h"


static uint32_t __check_free_frame_continuity(uint32_t frame, uint32_t num_frames)
{
	for (uint32_t i = 0; i < num_frames; ++i)
	{
		if (pmm_test_frame(frame + i) != FRAME_FREE)
			return (ERR_NO_FRAME);
	}
	return (frame);
}

// find the first free frame of memory for a given size
static uint32_t __find_first_free_frame(uint32_t num_frames)
{
	if (num_frames == 0)
		return (ERR_NO_FRAME);

	size_t num_chunks = BITMAP_SIZE(g_max_frames);
	for (size_t chunk = 0; chunk < num_chunks; ++chunk)
	{
		if (g_memory_map[chunk] == FRAME_CHUNK_FULL)
			continue;

		for (uint8_t bit = 0; bit < FRAMES_PER_CHUNK; ++bit)
		{
			uint32_t tested_bit_mask = BIT_MASK(bit);
			if (g_memory_map[chunk] & tested_bit_mask)
				continue;

			uint32_t frame = __check_free_frame_continuity(FRAME_FROM_CHUNKBIT(chunk, bit), num_frames);
			if (frame != ERR_NO_FRAME)
				return (frame);
		}
	}
	return (ERR_NO_FRAME);
}

void pmm_init(uint32_t start_address, uint32_t size)
{
	g_memory_map = (uint32_t*)start_address;
	g_max_frames = size / FRAME_SIZE;  
	g_used_frames = g_max_frames;

	memset32(g_memory_map, FRAME_CHUNK_FULL, BITMAP_SIZE(g_max_frames));
}

void pmm_unmap_region(uint32_t base_address, uint32_t size)
{
	uint32_t align = base_address / FRAME_SIZE; // align the address to the frame size
	uint32_t num_frames = size / FRAME_SIZE; // calculate the number of frames in the region and align it to 4K frames

	while (num_frames > 0) {
		pmm_free_frame(align++);
		g_used_frames--;
		num_frames--;
	}
	pmm_set_frame(0);
}

void pmm_map_region(uint32_t base_address, uint32_t size)
{
	uint32_t align = base_address / FRAME_SIZE;
	uint32_t num_frames = size / FRAME_SIZE;

	while (num_frames > 0) {
		pmm_set_frame(align++);
		g_used_frames++;
		num_frames--;
	}
}

uint32_t *pmm_alloc_frames(uint32_t num_frames)
{
	if (g_max_frames - g_used_frames <= num_frames) {
		printk("Not enough free frames available\n");
		return (NULL); // not enough free frames available
	}

	uint32_t start_frame = __find_first_free_frame(num_frames);
	if (start_frame == ERR_NO_FRAME)
		return (NULL); // no free region of memory large enough found

	for (uint32_t i = 0; i < num_frames; ++i) {
		pmm_set_frame(start_frame + i);
		g_used_frames++;
	}

	// convert the frame number to a memory address and return it
	uint32_t start_address = start_frame * FRAME_SIZE;

	return ((uint32_t*)start_address);
}

void pmm_free_frames(uint32_t *address, uint32_t num_frames)
{
	uint32_t start_frame = (uint32_t)address / FRAME_SIZE;

	for (uint32_t i = 0; i < num_frames; ++i) {
		pmm_free_frame(start_frame + i);
		g_used_frames--;
	}
}