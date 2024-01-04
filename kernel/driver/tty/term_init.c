#include "driver/tty.h"

void	term_init()
{
	while (g_tty_index < TTY_COUNT)
	{
		g_tty[g_tty_index].color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		term_clear();
		++g_tty_index;
	}
	g_tty_index = 0;
}
