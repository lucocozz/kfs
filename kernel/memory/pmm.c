#include "../includes/memory.h"


uint32_t	*memory_map = NULL;
uint32_t	g_max_blocks = 0;
uint32_t	g_used_blocks = 0;


// set a block/bit as used
void set_block(uint32_t block)
{
	// Because our bitmap is an array of 32-bit integers, we need to:
	// divide the bit/block by 32 to get the index of the block in the array
	// then use the modulo operator to get the bit offset corresponding to the block we want to set
	// and use the bitwise OR operator to set the bit.
	memory_map[block / 32] |= BIT_MASK(block % 32);
}

// set a block/bit as free
void free_block(uint32_t block) {
	// Same as above, but we use the bitwise AND operator to clear the bit.
	memory_map[block / 32] &= BIT_UNMASK(block % 32);
}

// check if a block/bit is used
uint32_t test_block(uint32_t block) {
	return memory_map[block / 32] & BIT_MASK(block % 32);
}

// find the first free block of memory for a given size
int32_t find_first_free_block(uint32_t num_blocks) {
	if (num_blocks == 0) return -1;

	// test 32 blocks at a time
	for (uint32_t i = 0; i < g_max_blocks / 32; i++) {
		if (memory_map[i] != 0xFFFFFFFF) {
			// at least one bit is free in this 32bit chunk of memory
			// test each bit to find the first free block
			for (uint32_t j = 0; j < 32; j++) {
				uint32_t bit = 1 << j;
				if (!(memory_map[i] & bit)) {
					// found start of free region of memory
					uint32_t block = (i * 32) + bit; // block number (0 to g_max_blocks)
					uint32_t free_blocks = 0; // keep track of how many free blocks we've found
					for (uint32_t count = 0; count <= num_blocks; count++) {
						if (!test_block(block + count)) free_blocks++;
						if (free_blocks == num_blocks) {
							// found enough free blocks
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
	memory_map = (uint32_t*)start_address;
	g_max_blocks = size / FRAME_SIZE;
	g_used_blocks = g_max_blocks;

	memset32(memory_map, FRAMES_FULL_DWORD, BITMAP_SIZE(g_max_blocks));
}

void initialise_memory_region(uint32_t base_address, uint32_t size) {
	uint32_t align = base_address / FRAME_SIZE; // align the address to the block size
	uint32_t num_blocks = size / FRAME_SIZE; // calculate the number of blocks in the region and align it to 4K blocks

	for (; num_blocks > 0; num_blocks--) {
		free_block(align++);
		g_used_blocks--;
	}
	// Always set the first block as used to avoid memory overwriting the kernel
	set_block(0);
}

void deinitialise_memory_region(uint32_t base_address, uint32_t size) {
	uint32_t align = base_address / FRAME_SIZE;
	uint32_t num_blocks = size / FRAME_SIZE;

	for (; num_blocks > 0; num_blocks--) {
		set_block(align++);
		g_used_blocks++;
	}
}

// uint32_t *kmalloc(uint32_t size) {
// 	uint32_t num_blocks = size / BLOCK_SIZE;
// 	if (size % BLOCK_SIZE) num_blocks++;

// 	uint32_t *address = allocate_blocks(num_blocks);
// 	if (address == 0) return 0;

// 	return address;
// }

// void kfree(uint32_t *address, uint32_t size) {
// 	uint32_t num_blocks = size / BLOCK_SIZE;
// 	if (size % BLOCK_SIZE) num_blocks++;

// 	free_blocks(address, num_blocks);
// }

// Allocate a block of memory
uint32_t *allocate_blocks(uint32_t num_blocks) {
	if (g_max_blocks - g_used_blocks <= num_blocks) {
		printk("Not enough free blocks available\n");
		return 0; // not enough free blocks available
	}

	int32_t start_block = find_first_free_block(num_blocks);
	if (start_block == -1) return 0; // no free region of memory large enough found

	for (uint32_t i = 0; i < num_blocks; i++) {
		set_block(start_block + i);
		g_used_blocks++;
	}

	// convert the block number to a memory address and return it
	uint32_t start_address = start_block * FRAME_SIZE;

	printk("Allocated %d blocks at 0x%x\n", num_blocks, start_address);
	return (uint32_t*)start_address;
}


// Free a block of memory
void free_blocks(uint32_t *address, uint32_t num_blocks) {
	uint32_t start_block = (uint32_t)address / FRAME_SIZE;

	for (uint32_t i = 0; i < num_blocks; i++) {
		free_block(start_block + i);
		g_used_blocks--;
	}
	printk("Freed %d blocks at 0x%x\n", num_blocks, address);
}