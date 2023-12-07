#include "kernel.h"

t_vga_terminal	g_term = {
	.row = 0,
	.column = 0,
	.color = 0,
	.buffer = (uint16_t*)0xB8000
};

void	kernel_main()
{
	term_init();
	term_puts("Hello, Kernel World!");
}
