#ifndef KERNEL_SYMBOL_TABLE_H
#define KERNEL_SYMBOL_TABLE_H

#include <stdint.h>
#include <stddef.h>

#include "printk.h"
#include "utils.h"

#define SYMBOL_SECTION_NAME "symbol_table"

typedef struct SymbolTableEntry {
	uint32_t	address;
	char		*name;
} SymbolTableEntry_t;

#define EXPORT_SYMBOL(func) \
	SymbolTableEntry_t __symbol_##func __Section__(SYMBOL_SECTION_NAME) = { \
		.address = (uint32_t)&func, \
		.name = #func \
	}

extern SymbolTableEntry_t	__start_symbol_table;
extern SymbolTableEntry_t	__stop_symbol_table;

char		*symbol_lookup_addr(uint32_t address);
uint32_t	symbol_lookup_name(char *name);
void		symbol_table_print(void);

#endif
