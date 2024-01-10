#include "symbol_table.h"
#include "string.h"
#include "printk.h"

SymbolTableEntry_t g_symbol_table[] __used = {
	{ .address = 0, .name = NULL }
};

char	*symbol_lookup_addr(uint32_t address)
{
	for (size_t i = 0; g_symbol_table[i].address; ++i) {
		if (g_symbol_table[i].address == address)
			return (g_symbol_table[i].name);
	}
	return (NULL);
}

uint32_t	symbol_lookup_name(char *name)
{
	for (size_t i = 0; g_symbol_table[i].address; ++i) {
		if (strcmp(g_symbol_table[i].name, name) == 0)
			return (g_symbol_table[i].address);
	}
	return (0);
}

void	symbol_table_print(void)
{
	printk("Symbol table:\n");
	for (size_t i = 0; g_symbol_table[i].address; ++i) {
		printk(".%s:%08x\n", g_symbol_table[i].name, g_symbol_table[i].address);
	}
}

void	symbol_add_entry(char *name, uint32_t address)
{
	size_t	i = 0;

	for (; g_symbol_table[i].address != 0; ++i) {
		if (g_symbol_table[i].address == address) {
			printk(KERN_ERR "Symbol %s already exists\n", name);
			return ;
		}
	}
	g_symbol_table[i].address = address;
	g_symbol_table[i].name = name;
	printk(KERN_INFO "Symbol %s added at %08x\n", name, address);
}
