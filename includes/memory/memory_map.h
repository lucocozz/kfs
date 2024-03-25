#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "multiboot.h"


typedef struct {
	uint32_t start;
	uint32_t end;
	uint32_t length;
} kernel_section_t;

typedef struct s_kernel_memory_map
{
	/* Kernel Sections */
	struct
	{
		kernel_section_t kernel;
		kernel_section_t text;
		kernel_section_t rodata;
		kernel_section_t data;
		kernel_section_t bss;
	} sections;
} kernel_memory_map_t;

extern uint32_t _kernel_start_virtual;
extern uint32_t _kernel_end_virtual;
extern uint32_t _kernel_start_physical;
extern uint32_t _kernel_end_physical;

extern uint32_t _stext;
extern uint32_t _etext;

extern uint32_t _srodata;
extern uint32_t _erodata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;


extern kernel_memory_map_t  g_kernel_memory_map;
extern multiboot_info_t     *g_boot_info;

extern uint32_t *main_memory_start;
extern uint32_t main_memory_length;
extern uint32_t nb_frames;

void     memory_map_init(multiboot_info_t *boot_info);
void     get_memory_map(void);

#endif // MEMORY_MAP_H