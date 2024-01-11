#include "driver/tty.h"

void	term_set_text_color(enum vga_color color)
{
	term_set_color(color, g_tty[g_tty_index].bg);
}
