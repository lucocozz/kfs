#include "driver/tty.h"

void	term_set_index(size_t index)
{
	g_tty[g_tty_index].column = index % VGA_WIDTH;
	g_tty[g_tty_index].row = index / VGA_WIDTH;
	set_vga_cursor(g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}