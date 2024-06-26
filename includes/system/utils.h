#ifndef KERNEL_SYSTEM_UTILS_H
#define KERNEL_SYSTEM_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#include "printk.h"

typedef uint8_t		u8;
typedef int8_t		i8;
typedef uint16_t	u16;
typedef int16_t		i16;
typedef uint32_t	u32;
typedef int32_t		i32;
typedef u16			uint;

#define UNUSED(x)	(void)(x)
#define ASM(...)	__asm__ volatile(__VA_ARGS__)

#define ARRAY_SIZE(x)			(sizeof(x) / sizeof(*x))
#define CEIL_DIV(a, b)			(((a + b) - 1) / b) // a / b rounded up
#define ALIGN_DOWN(a, b)		(a + b) & ~b
#define ALIGN_UP(a, b)			(((a + b) - 1) & ~(b - 1))
#define ALIGN_WITH(size, align)	((size + align - 1) & ~(align - 1))

#define LOW_B16(address)	(uint16_t)((address) & 0xFFFF)
#define HIGH_B16(address)	(uint16_t)(((address) >> 16) & 0xFFFF)
#define LOW_B8(address)		(uint8_t)((address) & 0xFF)
#define HIGH_B8(address)	(uint8_t)(((address) >> 8) & 0xFF)
#define BIT_MASK(bit)		(1UL << bit)
#define BIT_UNMASK(bit)		~(1UL << bit)

#define BYTE_TO_KB(byte)	(byte / 1024)
#define BYTE_TO_MB(byte)	(byte / 1024 / 1024)
#define BYTE_TO_GB(byte)	(byte / 1024 / 1024 / 1024)

#define KB_TO_BYTE(kb)		(kb * 1024)
#define KB_TO_MB(kb)		(kb / 1024)
#define KB_TO_GB(kb)		(kb / 1024 / 1024)

#define MB_TO_BYTE(mb)		(mb * 1024 * 1024)
#define MB_TO_KB(mb)		(mb * 1024)
#define MB_TO_GB(mb)		(mb / 1024)

#define GB_TO_BYTE(gb)		(gb * 1024 * 1024 * 1024)
#define GB_TO_KB(gb)		(gb * 1024 * 1024)
#define GB_TO_MB(gb)		(gb * 1024)


#define __Packed__			__attribute__((__packed__))
#define __Aligned__(x)		__attribute__((__aligned__(x)))
#define __Section__(name)	__attribute__((__section__(name)))
#define __Used__			__attribute__((__used__))
#define __Init__			__attribute__((__constructor__))
#define __Exit__			__attribute__((__destructor__))
#define __Cleanup__(addr)	__attribute__((__cleanup__(addr)))

#ifdef _DEBUG_

#define DEBUG(x) printk("DEBUG %s:%d: %s\n", __FILE__, __LINE__, #x)
#define DEBUGF(fmt, ...) printk("DEBUG %s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)

#else

#define DEBUG(...)
#define DEBUGF(...)

#endif

void panic(const char *format, ...);

#endif
