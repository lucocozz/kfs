#include "../includes/memory.h"

// set a frame/bit as used
void set_frame(uint32_t frame)
{
	uint32_t frame_chunk = FRAME_CHUNK(frame);
	uint32_t frame_bit = FRAME_BIT(frame);
	// Because our bitmap is an array of 32-bit integers, we need to:
	// divide the bit/frame by 32 to get the index of the frame in the array
	// then use the modulo operator to get the bit offset corresponding to the frame we want to set
	// and use the bitwise OR operator to set the bit.
	g_frames[frame_chunk] |= BIT_MASK(frame_bit);
}

// set a frame/bit as free
void free_frame(uint32_t frame)
{
	uint32_t frame_chunk = FRAME_CHUNK(frame);
	uint32_t frame_bit = FRAME_BIT(frame);
	
	// Same as above, but we use the bitwise AND operator to clear the bit.
	g_frames[frame_chunk] &= BIT_UNMASK(frame_bit);
}

// check if a frame/bit is used
uint32_t test_frame(uint32_t frame) {
	uint32_t frame_chunk = FRAME_CHUNK(frame);
	uint32_t frame_bit = FRAME_BIT(frame);

	return (g_frames[frame_chunk] & BIT_MASK(frame_bit));
}


static uint32_t __check_free_frame_continuity(uint32_t frame, uint32_t num_frames)
{
	for (uint32_t i = 0; i < num_frames; i++)
	{
		if (test_frame(frame + i) != FRAME_FREE)
			return (ERR_NO_FRAME);
	}
	return (num_frames);
}

// find the first free frame of memory for a given size
static uint32_t __find_first_free_frame(uint32_t num_frames)
{
	if (num_frames == 0)
		return (ERR_NO_FRAME);

	size_t num_chunks = BITMAP_SIZE(g_max_frames);
	for (size_t chunk = 0; chunk < num_chunks; ++chunk)
	{
		if (g_frames[chunk] == FRAMES_FULL_DWORD)
			continue;

		for (uint8_t bit = 0; bit < FRAMES_PER_DWORD; ++bit)
		{
			uint32_t tested_bit_mask = BIT_MASK(bit);
			if (g_frames[chunk] & tested_bit_mask)
				continue;
			
			uint32_t frame = __check_free_frame_continuity(ADDR_FROM_BITFRAME(chunk, bit), num_frames);
			if (frame != ERR_NO_FRAME)
				return (frame);
		}
	}
	return (ERR_NO_FRAME);
}

void initialise_memory_manager(uint32_t start_address, uint32_t size) {
	g_frames = (uint32_t*)start_address;
	g_max_frames = size / FRAME_SIZE;
	g_used_frames = g_max_frames;

	memset32(g_frames, FRAMES_FULL_DWORD, BITMAP_SIZE(g_max_frames));
}

void initialise_memory_region(uint32_t base_address, uint32_t size) {
	uint32_t align = base_address / FRAME_SIZE; // align the address to the frame size
	uint32_t num_frames = size / FRAME_SIZE; // calculate the number of frames in the region and align it to 4K frames

	for (; num_frames > 0; num_frames--) {
		free_frame(align++);
		g_used_frames--;
	}
	// Always set the first frame as used to avoid memory overwriting the kernel
	set_frame(0);
}

void deinitialise_memory_region(uint32_t base_address, uint32_t size) {
	uint32_t align = base_address / FRAME_SIZE;
	uint32_t num_frames = size / FRAME_SIZE;

	for (; num_frames > 0; num_frames--) {
		set_frame(align++);
		g_used_frames++;
	}
}

// uint32_t *kmalloc(uint32_t size) {
// 	uint32_t num_frames = size / frame_SIZE;
// 	if (size % frame_SIZE) num_frames++;

// 	uint32_t *address = allocate_frames(num_frames);
// 	if (address == 0) return 0;

// 	return address;
// }

// void kfree(uint32_t *address, uint32_t size) {
// 	uint32_t num_frames = size / frame_SIZE;
// 	if (size % frame_SIZE) num_frames++;

// 	free_frames(address, num_frames);
// }

// Allocate a frame of memory
uint32_t *allocate_frames(uint32_t num_frames) {
	if (g_max_frames - g_used_frames <= num_frames) {
		printk("Not enough free frames available\n");
		return (0); // not enough free frames available
	}

	uint32_t start_frame = __find_first_free_frame(num_frames);
	if (start_frame == ERR_NO_FRAME)
		return (0); // no free region of memory large enough found

	for (uint32_t i = 0; i < num_frames; i++) {
		set_frame(start_frame + i);
		g_used_frames++;
	}

	// convert the frame number to a memory address and return it
	uint32_t start_address = start_frame * FRAME_SIZE;

	printk("Allocated %d frames at 0x%x\n", num_frames, start_address);
	return ((uint32_t*)start_address);
}


// Free a frame of memory
void free_frames(uint32_t *address, uint32_t num_frames) {
	uint32_t start_frame = (uint32_t)address / FRAME_SIZE;

	for (uint32_t i = 0; i < num_frames; i++) {
		free_frame(start_frame + i);
		g_used_frames--;
	}
	printk("Freed %d frames at 0x%x\n", num_frames, address);
}