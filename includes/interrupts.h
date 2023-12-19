#ifndef LIBK_INTERRUPTS_H
#define LIBK_INTERRUPTS_H

#include <stdint.h>
#include <endian.h>

/// IDT size of 256 interrupts
#define IDT_ENTRIES 256
/// kernel code segment offset in GDT
#define KERNEL_CS 0x08 

/// Interrupt Descriptor Table (IDT) gate
typedef struct idt_gate {
	uint16_t	low_offset;
	uint16_t	selector;
	uint8_t		__zero;
	union
	{
		uint8_t	flags;
		struct
		{
			#if __BYTE_ORDER == __LITTLE_ENDIAN
			uint8_t	flag_type: 3;
			uint8_t	flag_storage: 1;
			uint8_t __flag_zero: 1;
			uint8_t	flag_privilege: 2;
			uint8_t	flag_present: 1;
			#else
			uint8_t	flag_present: 1;
			uint8_t	flag_privilege: 2;
			uint8_t __flag_zero: 1;
			uint8_t	flag_storage: 1;
			uint8_t	flag_type: 3;
			#endif
		};
	};
	uint16_t	high_offset;
} __attribute__((__packed__)) idt_gate_t;

typedef struct {
	// Data segment selector
	uint32_t	ds;
	// Pushed by pusha
	uint32_t	edi, esi, ebp, esp, ebx, edx, ecx, eax;
	// Interrupt number and error code (if applicable)
	uint32_t	int_no, err_code;
	// Pushed by the processor automatically
	uint32_t	eip, cs, eflags, useresp, ss;
} registers_t;

extern idt_gate_t idt[IDT_ENTRIES];

#endif
