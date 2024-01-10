#ifndef KERNEL_SYMBOL_TABLE_H
#define KERNEL_SYMBOL_TABLE_H

#include "printk.h"
#include <stdint.h>
#include <stddef.h>

#define __section(name) __attribute__((__section__(name)))
#define __used __attribute__((__used__))
#define __init __attribute__((__constructor__))
#define __exit __attribute__((__destructor__))

typedef struct SymbolTableEntry {
	uint32_t	address;
	char		*name;
} SymbolTableEntry_t;

#define EXPORT_SYMBOL(func) \
	SymbolTableEntry_t func##_symbol __section(".symbol_table"); \
	char *func##_name = #func; \
	__init void __init_##func(void) { \
		symbol_add_entry(func##_name, (uint32_t)func); \
	}

extern SymbolTableEntry_t g_symbol_table[];

char		*symbol_lookup_addr(uint32_t address);
uint32_t	symbol_lookup_name(char *name);
void		symbol_table_print(void);
void		symbol_add_entry(char *name, uint32_t address);

#endif
