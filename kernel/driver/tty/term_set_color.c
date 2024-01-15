#include "driver/tty.h"

void	term_set_color(enum vga_color fg, enum vga_color bg)
{
	g_tty[g_tty_index].color = vga_color(fg, bg);
}
EXPORT_SYMBOL(term_set_color);