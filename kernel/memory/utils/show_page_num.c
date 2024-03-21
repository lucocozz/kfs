#include "memory.h"

static int	__print_pages(page_queue_t *queue, const char *type)
{
	printk("%s: %d page(s)\n", type, queue->count);
	return (queue->count);
}

void	show_page_num(void)
{
	size_t	total = 0;

	// pthread_mutex_lock(&g_heap_mutex);
	total += __print_pages(&g_heap.tiny, "TINY");
	total += __print_pages(&g_heap.small, "SMALL");
	total += __print_pages(&g_heap.large, "LARGE");
	printk("Total : %d page(s)\n", total);
	// pthread_mutex_unlock(&g_heap_mutex);
}
