#include "memory/vmm.h"

void	print_free_list(void)
{
	page_free_t	*page = g_free_list;

	printk("--------------------------\n");
	printk("|       Free list        |\n");
	printk("--------------------------\n");
	printk("| Page at     | Count    |\n");
	printk("--------------------------\n");
	while (page != NULL) {
		printk("| 0x%08X  | %d        |\n", page, page->count);
		page = page->next;
	}
	printk("--------------------------\n");
}