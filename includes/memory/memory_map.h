#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include "multiboot.h"

typedef struct s_kernel_memory_map
{
    /* Kernel Sections */
    struct
    {
        /* Kernel Section */
        struct
        {
            uint32_t start;
            uint32_t end;
            uint32_t length;
        } kernel;

        /* Kernel Text Section */
        struct
        {
            uint32_t start;
            uint32_t end;
            uint32_t length;
        } text;

        /* Kernel Rodata Section */
        struct
        {
            uint32_t start;
            uint32_t end;
            uint32_t length;
        } rodata;

        /* Kernel Data Section */
        struct
        {
            uint32_t start;
            uint32_t end;
            uint32_t length;
        } data;

        /* Kernel BSS Section */
        struct
        {
            uint32_t start;
            uint32_t end;
            uint32_t length;
        } bss;
    } sections;

	uint32_t total_memory_length;
} kernel_memory_map_t;

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;

extern uint32_t _stext;
extern uint32_t _etext;

extern uint32_t _srodata;
extern uint32_t _erodata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;


extern kernel_memory_map_t kernel_memory_map;

extern multiboot_info_t	*g_boot_info;

int init_memory_map(multiboot_info_t *boot_info);
int get_memory_map();

#endif // MEMORY_MAP_H