#include "kernel.h"

t_vga_terminal		g_term = {0};
keyboard_queue_t	g_keyboard_queue = {0};

static void	__init_kernel(void)
{
	term_init();
	term_puts("Terminal initialized\n");
	term_puts("Initializing interrupts...\n");
	interrupts_init();
	term_puts("Interrupts initialized\n");
}

void	kernel_main()
{
	__init_kernel();
	term_clear();
	term_puts("Hello, World!\n");
	while (1)
		term_putkey_from_queue();
}
