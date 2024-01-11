#include "symbol_table.h"
#include "string.h"
#include "printk.h"

char	*symbol_lookup_addr(uint32_t address)
{
	SymbolTableEntry_t	*entry = &__start_symbol_table;

	while (entry != &__stop_symbol_table) {
		if (entry->address == address)
			return (entry->name);
		++entry;
	}
	return (NULL);
}
EXPORT_SYMBOL(symbol_lookup_addr);

uint32_t	symbol_lookup_name(char *name)
{
	SymbolTableEntry_t	*entry = &__start_symbol_table;

	while (entry != &__stop_symbol_table) {
		if (strcmp(entry->name, name) == 0)
			return (entry->address);
		++entry;
	}
	return (0);
}
EXPORT_SYMBOL(symbol_lookup_name);

void	symbol_table_print(void)
{
	SymbolTableEntry_t	*entry = &__start_symbol_table;
	
	printk("Symbol table:\n");
	while (entry != &__stop_symbol_table) {
		printk("  %08p <%s>\n", entry->address, entry->name);
		++entry;
	}
}
EXPORT_SYMBOL(symbol_table_print);
