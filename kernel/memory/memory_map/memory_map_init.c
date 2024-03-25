#include "memory/memory_map.h"
#include "../includes/memory.h"
#include "shell/builtin.h"
#include "multiboot.h"
#include "assert.h"
#include "system/utils.h"
#include "kernel.h"

multiboot_info_t	*g_boot_info = NULL;
memory_map_t		g_memory_map = {0};

static int __check_flags(void)
{
	CHECK_AND_LOG_FLAG(g_boot_info, 0, "FLAGS");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_MEMORY, "MEMORY");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_BOOTDEV, "BOOTDEV");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_DEVICE, "DEVICE");
	return (0);
}

static void	__set_section_limit(kernel_section_t *section, uint32_t start, uint32_t end)
{
	section->start = start;
	section->end = end;
	section->length = end - start;
}

static void __sections_init(void)
{
	__set_section_limit(&g_memory_map.kernel_physical, (uint32_t)&_kernel_start_physical, (uint32_t)&_kernel_end_physical);
	__set_section_limit(&g_memory_map.kernel_virtual, (uint32_t)&_kernel_start_virtual, (uint32_t)&_kernel_end_virtual);
	__set_section_limit(&g_memory_map.text, (uint32_t)&_stext, (uint32_t)&_etext);
	__set_section_limit(&g_memory_map.rodata, (uint32_t)&_srodata, (uint32_t)&_erodata);
	__set_section_limit(&g_memory_map.data, (uint32_t)&_sdata, (uint32_t)&_edata);
	__set_section_limit(&g_memory_map.bss, (uint32_t)&_sbss, (uint32_t)&_ebss);
}

void	memory_map_init(multiboot_info_t *boot_info)
{
	g_boot_info = (multiboot_info_t*)((uint32_t)boot_info + KERNEL_START);
	g_boot_info->mmap_addr += KERNEL_START;

	__check_flags();
	__sections_init();
}
EXPORT_SYMBOL(memory_map_init);
