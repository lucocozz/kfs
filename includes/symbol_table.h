#ifndef KERNEL_SYMBOL_TABLE_H
#define KERNEL_SYMBOL_TABLE_H

#include <stdint.h>
#include <stddef.h>

#define __section(name) __attribute__((__section__(name)))
#define __used __attribute__((__used__))
#define __unused __attribute__((__unused__))
#define __packed __attribute__((__packed__))
#define __aligned(n) __attribute__((__aligned__(n)))
#define __noreturn __attribute__((__noreturn__))
#define __always_inline __attribute__((__always_inline__))
#define __weak __attribute__((__weak__))
#define __deprecated __attribute__((__deprecated__))
#define __malloc __attribute__((__malloc__))
#define __pure __attribute__((__pure__))
#define __const __attribute__((__const__))

typedef struct SymbolTableEntry {
	uint32_t	address;
	char		*symbol;
} SymbolTableEntry_t;

#define EXPORT_SYMBOL(name) \
	SymbolTableEntry_t __attribute__((__used__, __section__("symbol_table"))) name##_symbol = { \
		.address = (uint32_t)&name, \
		.symbol = #name \
	}

extern SymbolTableEntry_t symbol_table[];

char		*symbol_lookup_addr(uint32_t address);
uint32_t	symbol_lookup_name(char *name);
void		symbol_table_print(void);

#endif
