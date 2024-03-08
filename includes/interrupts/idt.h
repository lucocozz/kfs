#ifndef KERNEL_INTERRUPTS_IDT_H
#define KERNEL_INTERRUPTS_IDT_H

#include <stddef.h>

#define IDT_SIZE 256

#define INTERRUPT_DIVIDE_BY_ZERO				0
#define INTERRUPT_DEBUG			 				1
#define INTERRUPT_NMI							2 
#define INTERRUPT_BREAKPOINT					3
#define INTERRUPT_OVERFLOW						4
#define INTERRUPT_BOUND_RANGE_EXCEEDED			5
#define INTERRUPT_INVALID_OPCODE				6
#define INTERRUPT_DEVICE_NOT_AVAILABLE			7
#define INTERRUPT_DOUBLE_FAULT					8
#define INTERRUPT_COPROCESSOR_SEGMENT_OVERRUN	9
#define INTERRUPT_INVALID_TSS					10
#define INTERRUPT_SEGMENT_NOT_PRESENT			11
#define INTERRUPT_STACK_SEGMENT_FAULT			12
#define INTERRUPT_GENERAL_PROTECTION_FAULT		13
#define INTERRUPT_PAGE_FAULT					14
#define INTERRUPT_RESERVED						15
#define INTERRUPT_MATH_FAULT					16
#define INTERRUPT_ALIGNMENT_CHECK				17
#define INTERRUPT_MACHINE_CHECK					18
#define INTERRUPT_SIMD_FLOATING_POINT			19
#define INTERRUPT_VIRTUALIZATION				20
#define INTERRUPT_TIMER							32
#define INTERRUPT_KEYBOARD						33
#define INTERRUPT_SYSCALL						128


typedef struct IDT {
	uint16_t	size;
	uint32_t	address;
} __attribute__((packed)) IDT_t;

typedef struct IDT_entry {
	uint16_t	isr_low;
	uint16_t	selector;
	uint8_t		_reserved;
	uint8_t		flags;
	uint16_t	isr_high;
} __attribute__((packed)) IDT_entry_t;


extern IDT_t		g_idt_ptr;
extern IDT_entry_t	g_idt[IDT_SIZE];


void	idt_init(void);
void	idt_load(uint32_t idt_ptr);
void	idt_set(uint8_t interrupt, uint32_t isr);

#endif
