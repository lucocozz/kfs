#include "cpu/memory_segments.h"
#include "string.h"

gdt_entry_t gdt_entries[SEGMENT_DESCRIPTOR_COUNT] = {0};

void	gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = gran;
	gdt_entries[num].access = access;
}

void	gdt_init(void)
{
	gdt_ptr_t gdt_ptr;

	gdt_ptr.limit = (sizeof(gdt_entry_t) * SEGMENT_DESCRIPTOR_COUNT);
	gdt_ptr.base = (uint32_t)GDT_ADDRESS;

	gdt_set_gate(0, 0, 0, 0, 0);													// Null segment
	gdt_set_gate(1, 0, SEGMENT_LIMIT, SEGMENT_KERNEL_CODE, SEGMENT_GRANULARITY);	// Kernel mode Code segment
	gdt_set_gate(2, 0, SEGMENT_LIMIT, SEGMENT_KERNEL_DATA, SEGMENT_GRANULARITY);	// Kernel mode Data segment
	gdt_set_gate(3, 0, SEGMENT_LIMIT, SEGMENT_KERNEL_STACK, SEGMENT_GRANULARITY);	// Kernel mode Stack segment
	gdt_set_gate(4, 0, SEGMENT_LIMIT, SEGMENT_USER_CODE, SEGMENT_GRANULARITY);		// User mode code segment
	gdt_set_gate(5, 0, SEGMENT_LIMIT, SEGMENT_USER_DATA, SEGMENT_GRANULARITY);		// User mode data segment
	gdt_set_gate(6, 0, SEGMENT_LIMIT, SEGMENT_USER_STACK, SEGMENT_GRANULARITY);		// User mode stack segment

	memcpy((void *)gdt_ptr.base, (void *)gdt_entries, gdt_ptr.limit);

	gdt_flush((uint32_t)&gdt_ptr);
}
