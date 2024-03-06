#include "memory/memory_map.h"
#include "memory/memory.h"
#include "shell/builtin.h"
#include "multiboot.h"
#include "assert.h"

kernel_memory_map_t	kernel_memory_map;


multiboot_info_t	*g_boot_info = NULL;

int init_memory_map(multiboot_info_t *boot_info)
{
	g_boot_info = (multiboot_info_t*)((uint32_t)boot_info + KERNEL_START);
	g_boot_info->mmap_addr += KERNEL_START;

	// Check flags
	CHECK_AND_LOG_FLAG(g_boot_info, 0, "FLAGS");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_MEMORY, "MEMORY");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_BOOTDEV, "BOOTDEV");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_DEVICE, "DEVICE");

	return (0);
}
EXPORT_SYMBOL(init_memory_map);

int get_memory_map()
{
	assert(g_boot_info != NULL);

	kernel_memory_map.sections.kernel.start = (uint32_t)&_kernel_start;
	kernel_memory_map.sections.kernel.end = (uint32_t)&_kernel_end;
	kernel_memory_map.sections.kernel.length = kernel_memory_map.sections.kernel.end - kernel_memory_map.sections.kernel.start;

	kernel_memory_map.sections.text.start = (uint32_t)&_stext;
	kernel_memory_map.sections.text.end = (uint32_t)&_etext;
	kernel_memory_map.sections.text.length = kernel_memory_map.sections.text.end - kernel_memory_map.sections.text.start;

	kernel_memory_map.sections.rodata.start = (uint32_t)&_srodata;
	kernel_memory_map.sections.rodata.end = (uint32_t)&_erodata;
	kernel_memory_map.sections.rodata.length = kernel_memory_map.sections.rodata.end - kernel_memory_map.sections.rodata.start;

	kernel_memory_map.sections.data.start = (uint32_t)&_sdata;
	kernel_memory_map.sections.data.end = (uint32_t)&_edata;
	kernel_memory_map.sections.data.length = kernel_memory_map.sections.data.end - kernel_memory_map.sections.data.start;

	kernel_memory_map.sections.bss.start = (uint32_t)&_sbss;
	kernel_memory_map.sections.bss.end = (uint32_t)&_ebss;
	kernel_memory_map.sections.bss.length = kernel_memory_map.sections.bss.end - kernel_memory_map.sections.bss.start;

	kernel_memory_map.total_memory_length = g_boot_info->mem_upper + g_boot_info->mem_lower;

	mmap_print();

	// physical memory map
	printk("Kernel physical start  : 0x%X\n", kernel_memory_map.sections.kernel.start - KERNEL_START);
	printk("Kernel physical end    : 0x%X\n", kernel_memory_map.sections.kernel.end - KERNEL_START);
	printk("Kernel physical length : 0x%X\n", kernel_memory_map.sections.kernel.length);
	printk("\n");

	// virtual memory map
	printk("Kernel virtual start   : 0x%X\n", kernel_memory_map.sections.kernel.start);
	printk("Kernel virtual end     : 0x%X\n", kernel_memory_map.sections.kernel.end);
	printk("Kernel virtual length  : 0x%X\n", kernel_memory_map.sections.kernel.length);
	printk("\n");

	// Total memory
	printk("Memory Lower : %dKB\n", g_boot_info->mem_lower);
	printk("Memory Upper : %dKB\n", g_boot_info->mem_upper);
	printk("Total Memory : %dMB\n", kernel_memory_map.total_memory_length / 1024);

	return (0);
}
EXPORT_SYMBOL(get_memory_map);