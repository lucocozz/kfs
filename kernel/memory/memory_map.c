#include "memory/memory_map.h"
#include "memory.h"
#include "shell/builtin.h"
#include "multiboot.h"
#include "assert.h"
#include "system/utils.h"
#include "kernel.h"

multiboot_info_t	*g_boot_info = NULL;
kernel_memory_map_t	kernel_memory_map = {0};

int check_flags(void)
{
	CHECK_AND_LOG_FLAG(g_boot_info, 0, "FLAGS");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_MEMORY, "MEMORY");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_BOOTDEV, "BOOTDEV");
    CHECK_AND_LOG_FLAG(g_boot_info, MULTIBOOT_INFO_DEVICE, "DEVICE");
	return (0);
}

void init_sections_struct(void)
{
	kernel_memory_map.sections.kernel.start = (uint32_t)&_kernel_start_virtual;
	kernel_memory_map.sections.kernel.end = (uint32_t)&_kernel_end_virtual;
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
}

int init_memory_map(multiboot_info_t *boot_info)
{
	g_boot_info = (multiboot_info_t*)((uint32_t)boot_info + KERNEL_START);
	g_boot_info->mmap_addr += KERNEL_START;

	check_flags();
	init_sections_struct();

	printk("--------------------\n");
	printk("Physical Memory map\n");
	printk("--------------------\n");

	mmap_print();

	// uint32_t nb_of_mmap_entries = g_boot_info->mmap_length / sizeof(multiboot_mmap_entry_t);
    // multiboot_mmap_entry_t *mmap_entry = (multiboot_mmap_entry_t*)g_boot_info->mmap_addr + sizeof(multiboot_mmap_entry_t) * (nb_of_mmap_entries);
    // uint32_t total_memory = mmap_entry->addr_low + mmap_entry->len_low - 1;
	uint32_t total_memory = MAX_MEMORY_SIZE; // 4GB address space for 32 bits = 0xFFFFFFFF

    printk("MAx memory size in bytes (for a 32 bits system): 0x%X \n", total_memory);
	// this is the nb blocks for the full 32 bits address space, we're mapping 4GB even if we have less memory
	printk("Total 4K blocks: 0x%x\n", total_memory * 1024 / FRAME_SIZE);

    initialise_memory_manager((uint32_t)&_kernel_end_physical, total_memory);

	for (uint32_t i = 0; i < g_boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t))
	{
		multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t*)(g_boot_info->mmap_addr + i);

		if(entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
            initialise_memory_region(entry->addr_low, entry->len_low);
		}
	}

	// set kernel memory as used and align it to 4K blocks above the kernel
	uint32_t kernel_memory_length = ((uint32_t)&_kernel_end_physical - (uint32_t)&_kernel_start_physical + FRAME_SIZE - 1) & ~(FRAME_SIZE - 1);
	deinitialise_memory_region((uint32_t)&_kernel_start_physical, kernel_memory_length);

	// reserve the memory map and align it to 4K blocks
	uint32_t memory_map_length = (max_blocks / FRAMES_PER_BYTE + FRAME_SIZE - 1) & ~(FRAME_SIZE - 1);
	deinitialise_memory_region((uint32_t)&_kernel_end_physical, memory_map_length);

	printk("Total blocks: 0x%u\n", max_blocks);
	printk("Used blocks: 0x%u\n", used_blocks);
	printk("Free blocks: 0x%u\n", max_blocks - used_blocks);

	return (0);
}

int get_memory_map()
{
	assert(g_boot_info != NULL);

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
	printk("Total Memory : %dMB (lower + upper)\n", (g_boot_info->mem_lower + g_boot_info->mem_upper) / 1024);

	return (0);
}
EXPORT_SYMBOL(get_memory_map);