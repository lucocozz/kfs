#ifndef KERNEL_CPU_MEMORY_SEGMENTS_H
#define KERNEL_CPU_MEMORY_SEGMENTS_H

#include <stdint.h>
#include "symbol_table.h"

#define GDT_ADDRESS 0x00000800

#define SEGMENT_DESCRIPTOR_COUNT 7

#define SEGMENT_BASE 0
#define SEGMENT_LIMIT 0xFFFFFFFF
#define SEGMENT_GRANULARITY 0xCF

#define SEGMENT_KERNEL_CODE 0x9B
#define SEGMENT_KERNEL_DATA 0x93
#define SEGMENT_KERNEL_STACK 0x0D
#define SEGMENT_USER_CODE 0xFF
#define SEGMENT_USER_DATA 0xF3
#define SEGMENT_USER_STACK 0x0D


typedef struct gdt_ptr_s {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

typedef struct gdt_entry_s {
	uint16_t	limit_low;
	uint16_t	base_low;
	uint8_t		base_middle;
	uint8_t		access;
	uint8_t		granularity;
	uint8_t		base_high;
} __attribute__((packed)) gdt_entry_t;

extern gdt_entry_t	gdt_entries[SEGMENT_DESCRIPTOR_COUNT];

extern void	gdt_flush(uint32_t);
void		gdt_init(void);
void		gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif
