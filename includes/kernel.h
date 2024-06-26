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

#include "assert.h"
#include "symbol_table.h"
#include "multiboot.h"
#include "printk.h"
#include "../includes/memory.h"

#include "system/utils.h"
#include "system/interrupts.h"
#include "system/signals.h"
#include "system/errno.h"
#include "system/process.h"

#include "driver/serials.h"
#include "driver/keyboard.h"
#include "driver/vga.h"
#include "driver/tty.h"

#include "shell/builtin.h"
#include "shell/shell.h"

#endif
