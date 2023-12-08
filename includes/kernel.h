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

#include "tty.h"
#include "vga.h"
#include "libc.h"

#endif
