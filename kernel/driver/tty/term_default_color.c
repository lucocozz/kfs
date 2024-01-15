#include "driver/tty.h"

void	term_default_color(void)
{
	term_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}
EXPORT_SYMBOL(term_default_color);
