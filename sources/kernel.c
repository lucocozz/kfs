#include "kernel.h"

t_vga_terminal	g_term = {0};

void	kernel_main()
{
	term_init();
	term_puts("Hello, Kernel World!");
}
