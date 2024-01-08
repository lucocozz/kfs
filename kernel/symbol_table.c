#include "symbol_table.h"
#include "string.h"
#include "printk.h"

SymbolTableEntry_t symbol_table[] = {
	{ .address = 0, .symbol = NULL }
};

char	*symbol_lookup_addr(uint32_t address)
{
	for (size_t i = 0; symbol_table[i].address; ++i) {
		if (symbol_table[i].address == address)
			return (symbol_table[i].symbol);
	}
	return (NULL);
}

uint32_t	symbol_lookup_name(char *name)
{
	for (size_t i = 0; symbol_table[i].address; ++i) {
		if (!strcmp(symbol_table[i].symbol, name))
			return (symbol_table[i].address);
	}
	return (0);
}

void	symbol_table_print(void)
{
	for (size_t i = 0; symbol_table[i].address; ++i) {
		printk(".%s:%08x\n", symbol_table[i].symbol, symbol_table[i].address);
	}
}