#include "memory/vmm.h"

void	print_free_list(void)
{
	page_free_t	*page = g_free_list;

	printk("Free list:");
	if (page == NULL) {
		printk(" Empty\n");
		return ;
	}
	printk("\n");

	while (page != NULL) {
		printk("Page at %p, count: %d\n", page, page->count);
		page = page->next;
	}
}