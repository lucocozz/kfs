#ifndef KERNEL_MEMORY_PMM_H
#define KERNEL_MEMORY_PMM_H

#include "system/utils.h"

// Maximum memory size for a 32-bit system
#define MAX_MEMORY_SIZE 0xFFFFFFFF

#define FRAME_SIZE						4096 
#define FRAMES_PER_CHUNK				32
#define FRAME_CHUNK_FULL				0xFFFFFFFF
#define FRAME_FREE						0x0
#define FRAME_FROM_CHUNKBIT(chunk, bit)	(chunk * FRAMES_PER_CHUNK + bit)
#define FRAME_CHUNK(addr)				(addr / FRAMES_PER_CHUNK)
#define FRAME_BIT(addr)					(addr % FRAMES_PER_CHUNK)

#define ERR_NO_FRAME (uint32_t)(-1)

/// Returns the size of the bitmap in 32-bit words. multiplies the size by 4 to get the size in bytes
#define BITMAP_SIZE(size)	(size / FRAMES_PER_CHUNK)


// Memory map
extern uint32_t *g_memory_map;
extern uint32_t g_max_frames;
extern uint32_t g_used_frames;


void		pmm_init(uint32_t start_address, uint32_t size);
void		pmm_unmap_region(uint32_t base_address, uint32_t size);
void		pmm_map_region(uint32_t base_address, uint32_t size);
uint32_t	*pmm_alloc_frames(uint32_t num_frames);
void		pmm_free_frames(uint32_t *address, uint32_t num_frames);


static inline void pmm_set_frame(uint32_t frame) {
	g_memory_map[FRAME_CHUNK(frame)] |= BIT_MASK(FRAME_BIT(frame));
}

static inline void pmm_unset_frame(uint32_t frame) {
	g_memory_map[FRAME_CHUNK(frame)] &= BIT_UNMASK(FRAME_BIT(frame));
}

static inline uint32_t pmm_test_frame(uint32_t frame) {
	return (g_memory_map[FRAME_CHUNK(frame)] & BIT_MASK(FRAME_BIT(frame)));
}


#endif