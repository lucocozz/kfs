#include "kernel.h"

t_vga_terminal		g_term = {0};
keyboard_buffer_t	g_keyboard_buffer = {0};

void	kernel_main()
{
	term_init();
	term_puts("Terminal initialized\n");
	term_puts("Initializing interrupts...\n");
	interrupts_init();
	term_puts("Interrupts initialized\n");
	term_clear();
	term_puts("Hello, World!\n");
	while (1);
}
