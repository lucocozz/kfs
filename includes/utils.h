#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#include "printk.h"


#define UNUSED(x)		(void)(x)
#define PAUSE_RUNTIME	printk("PAUSE_RUNTIME\n"); while (1) asm volatile("hlt")
#define KERNEL_PANIC	printk("KERNEL PANIC!\n"); while (1) asm volatile("hlt")

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(*x))
#define CEIL_DIV(a, b)	(((a + b) - 1) / b) // a / b rounded up
#define ALIGN_DOWN(a, b)	(a + b) & ~b
#define ALIGN_UP(a, b)		(((a + b) - 1) & ~(b - 1))

#define LOW_B16(address)	(uint16_t)((address) & 0xFFFF)
#define HIGH_B16(address)	(uint16_t)(((address) >> 16) & 0xFFFF)
#define LOW_B8(address)		(uint8_t)((address) & 0xFF)
#define HIGH_B8(address)	(uint8_t)(((address) >> 8) & 0xFF)

#define __packed 		__attribute__((__packed__))
#define __aligned(x)	__attribute__((__aligned__(x)))
#define __section(name) __attribute__((__section__(name)))
#define __used			__attribute__((__used__))
#define __init			__attribute__((__constructor__))
#define __exit			__attribute__((__destructor__))
#define __cleanup(addr)	__attribute__((__cleanup__(addr)))

#ifdef _DEBUG_

#define DEBUG(x) printk("DEBUG %s:%d: %s\n", __FILE__, __LINE__, #x)
#define DEBUGF(fmt, ...) printk("DEBUG %s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)

#else

#define DEBUG(...)
#define DEBUGF(...)

#endif


#endif
