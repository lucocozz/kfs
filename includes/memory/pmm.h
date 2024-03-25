#ifndef PMM_H
#define PMM_H

#include "system/utils.h"

// Maximum memory size for a 32-bit system
#define MAX_MEMORY_SIZE 0xFFFFFFFF

#define FRAME_SIZE			4096 
#define FRAMES_PER_BYTE		8
#define FRAMES_PER_DWORD	32
#define FRAMES_FULL_BYTE	0xFF
#define FRAMES_FULL_DWORD	0xFFFFFFFF

#define BITMAP_SIZE(size)	(size / FRAMES_PER_DWORD)
#define BITMAP_INDEX(addr) 	(addr / FRAMES_PER_DWORD)
#define BITMAP_OFFSET(addr)	(addr % FRAMES_PER_DWORD)


// Memory map
extern uint32_t *memory_map;
extern uint32_t g_max_blocks;
extern uint32_t g_used_blocks;


void		set_block(uint32_t block);
void		free_block(uint32_t block);
uint32_t	test_block(uint32_t block);
int32_t		find_first_free_block(uint32_t num_blocks);
void		initialise_memory_manager(uint32_t start_address, uint32_t size);
void		initialise_memory_region(uint32_t base_address, uint32_t size);
void		deinitialise_memory_region(uint32_t base_address, uint32_t size);
uint32_t	*allocate_blocks(uint32_t num_blocks);
void		free_blocks(uint32_t *address, uint32_t num_blocks);

#endif