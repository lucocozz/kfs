#ifndef KERNEL_SYMBOL_TABLE_H
#define KERNEL_SYMBOL_TABLE_H

#include "printk.h"
#include <stdint.h>
#include <stddef.h>

#define __section(name) __attribute__((__section__(name)))
#define __used __attribute__((__used__))
#define __init __attribute__((__constructor__))
#define __exit __attribute__((__destructor__))

#define SYMBOL_SECTION_NAME "symbol_table"

typedef struct SymbolTableEntry {
	uint32_t	address;
	char		*name;
} SymbolTableEntry_t;

#define EXPORT_SYMBOL(func) \
	SymbolTableEntry_t __symbol_##func __section(SYMBOL_SECTION_NAME) = { \
		.address = (uint32_t)&func, \
		.name = #func \
	}

extern SymbolTableEntry_t	__start_symbol_table;
extern SymbolTableEntry_t	__stop_symbol_table;

char		*symbol_lookup_addr(uint32_t address);
uint32_t	symbol_lookup_name(char *name);
void		symbol_table_print(void);

#endif
