#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include <stdint.h>
#include "symbol_table.h"
#include "interrupt/pic.h"
#include "utils.h"

#define IDT_ENTRIES_SIZE 256

#define INTERRUPT_DIVIDE_BY_ZERO				0x00
#define INTERRUPT_DEBUG			 				0x01
#define INTERRUPT_NMI							0x02
#define INTERRUPT_BREAKPOINT					0x03
#define INTERRUPT_OVERFLOW						0x04
#define INTERRUPT_BOUND_RANGE_EXCEEDED			0x05
#define INTERRUPT_INVALID_OPCODE				0x06
#define INTERRUPT_DEVICE_NOT_AVAILABLE			0x07
#define INTERRUPT_DOUBLE_FAULT					0x08
#define INTERRUPT_COPROCESSOR_SEGMENT_OVERRUN	0x09
#define INTERRUPT_INVALID_TSS					0x0A
#define INTERRUPT_SEGMENT_NOT_PRESENT			0x0B
#define INTERRUPT_STACK_SEGMENT_FAULT			0x0C
#define INTERRUPT_GENERAL_PROTECTION_FAULT		0x0D
#define INTERRUPT_PAGE_FAULT					0x0E
#define INTERRUPT_RESERVED						0x0F
#define INTERRUPT_MATH_FAULT					0x10
#define INTERRUPT_ALIGNMENT_CHECK				0x11
#define INTERRUPT_MACHINE_CHECK					0x12
#define INTERRUPT_SIMD_FLOATING_POINT			0x13
#define INTERRUPT_VIRTUALIZATION				0x14
#define INTERRUPT_TIMER							0x20
#define INTERRUPT_KEYBOARD						0x21
#define INTERRUPT_SYSCALL						0x80

#define INTERRUPT_MASK_ALL		0x00
#define INTERRUPT_MASK_SYSCALL	0x7F
#define INTERRUPT_MASK_KEYBOARD	0xFD
#define INTERRUPT_MASK_TIMER	0xFE
#define INTERRUPT_MASK_RESERVED	0xFF

/// kernel code segment offset in GDT
#define KERNEL_CODE_SEG 0x08

/// Interrupt Descriptor Table (IDT)
typedef struct IDT {
	uint16_t	size;
	uint32_t	address;
} __attribute__((packed)) IDT_t;

/// Interrupt Descriptor Table (IDT) entry
typedef struct IDT_entry {
	uint16_t	base_low;
	uint16_t	selector;
	uint8_t		zero;
	uint8_t		flags;
	uint16_t	base_high;
} __attribute__((packed)) IDT_entry_t;

typedef struct registers {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
} __attribute__((packed)) registers_t;

typedef struct stack_state {
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed)) stack_state_t;


extern IDT_t		g_idt;
extern IDT_entry_t	g_idt_entries[IDT_ENTRIES_SIZE];


void	interrupts_init(void);

void	idt_load(uint32_t address);
void	interrupt_handler_14(); // page fault
void	interrupt_handler_32(); // timer
void	interrupt_handler_33(); // keyboard
void	interrupt_handler_128(); // system call

void	interrupt_handler(registers_t regs, unsigned int interrupt, struct stack_state stack);

#endif
