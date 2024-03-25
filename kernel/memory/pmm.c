#include "../includes/memory.h"

// set a frame/bit as used
void set_frame(uint32_t frame)
{
	// Because our bitmap is an array of 32-bit integers, we need to:
	// divide the bit/frame by 32 to get the index of the frame in the array
	// then use the modulo operator to get the bit offset corresponding to the frame we want to set
	// and use the bitwise OR operator to set the bit.
	g_frames[frame / 32] |= BIT_MASK(frame % 32);
}

// set a frame/bit as free
void free_frame(uint32_t frame) {
	// Same as above, but we use the bitwise AND operator to clear the bit.
	g_frames[frame / 32] &= BIT_UNMASK(frame % 32);
}

// check if a frame/bit is used
uint32_t test_frame(uint32_t frame) {
	return g_frames[frame / 32] & BIT_MASK(frame % 32);
}

// find the first free frame of memory for a given size
int32_t find_first_free_frame(uint32_t num_frames) {
	if (num_frames == 0) return -1;

	// test 32 frames at a time
	for (uint32_t i = 0; i < g_max_frames / 32; i++) {
		if (g_frames[i] != FRAMES_FULL_DWORD) {
			// at least one bit is free in this 32bit chunk of memory
			// test each bit to find the first free frame
			for (uint32_t j = 0; j < 32; j++) {
				uint32_t bit = 1 << j;
				if (!(g_frames[i] & bit)) {
					// found start of free region of memory
					uint32_t frame = (i * 32) + bit; // frame number (0 to g_max_frames)
					uint32_t free_frames = 0; // keep track of how many free frames we've found
					for (uint32_t count = 0; count <= num_frames; count++) {
						if (!test_frame(frame + count)) free_frames++;
						if (free_frames == num_frames) {
							// found enough free frames
							return i*32 + j;
						}
					}
				}
			}
		}
	}
	return -1; // no free region of memory large enough found
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
		return 0; // not enough free frames available
	}

	int32_t start_frame = find_first_free_frame(num_frames);
	if (start_frame == -1) return 0; // no free region of memory large enough found

	for (uint32_t i = 0; i < num_frames; i++) {
		set_frame(start_frame + i);
		g_used_frames++;
	}

	// convert the frame number to a memory address and return it
	uint32_t start_address = start_frame * FRAME_SIZE;

	printk("Allocated %d frames at 0x%x\n", num_frames, start_address);
	return (uint32_t*)start_address;
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