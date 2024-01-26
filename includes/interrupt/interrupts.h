#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include <stdint.h>
#include "symbol_table.h"
#include "interrupt/pic.h"
#include "utils.h"

#define IDT_ENTRIES 256

#define INTERRUPT_PAGE_FAULT 14
#define INTERRUPT_TIMER 32
#define INTERRUPT_KEYBOARD 33
#define INTERRUPT_SYSCALL 128

#define INTERRUPT_MASK_ALL 0x00
#define INTERRUPT_MASK_TIMER 0xFE
#define INTERRUPT_MASK_KEYBOARD 0xFD
#define INTERRUPT_MASK_RESERVED 0xFF
#define INTERRUPT_MASK_SYSCALL 0x7F

/// kernel code segment offset in GDT
#define KERNEL_CODE_SEG 0x08

/// Interrupt Descriptor Table (IDT)
typedef struct IDT {
	uint16_t	size;
	uint32_t	address;
} __attribute__((packed)) IDT_t;

/// Interrupt Descriptor Table (IDT) entry
typedef struct IDTDescriptor {
	uint16_t	offset_low;
	uint16_t	segment_selector;
	uint8_t		__reserved;
	uint8_t		type_and_attr;
	uint16_t	offset_high;
} __attribute__((packed)) IDTDescriptor_t;

typedef struct cpu_state {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
} __attribute__((packed)) cpu_state_t;

typedef struct stack_state {
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed)) stack_state_t;


extern IDT_t			idt;
extern IDTDescriptor_t	idt_descriptors[IDT_ENTRIES];


void	interrupts_init();

void	load_idt(uint32_t address);
void	interrupt_handler_14(); // page fault
void	interrupt_handler_32(); // timer
void	interrupt_handler_33(); // keyboard
void	interrupt_handler_128(); // system call

void	interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack);

#endif
