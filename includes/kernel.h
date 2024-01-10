#ifndef KERNEL_H
#define KERNEL_H

#ifdef __linux__
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#ifndef __i386__
#error "This needs to be compiled with a ix86-elf compiler"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "libc.h"

#include "cpu/pic.h"
#include "cpu/interrupts.h"
#include "cpu/memory_segments.h"

#include "driver/ports.h"
#include "driver/tty.h"
#include "driver/vga.h"
#include "driver/keyboard.h"

#include "printk.h"
#include "symbol_table.h"

#define LOW_B16(address) (uint16_t)((address) & 0xFFFF)
#define HIGH_B16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define LOW_B8(address) (uint8_t)((address) & 0xFF)
#define HIGH_B8(address) (uint8_t)(((address) >> 8) & 0xFF)

void	dump_stack(void);

#endif
