#include "driver/tty.h"

void	term_reset_color(void)
{
	term_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}
EXPORT_SYMBOL(term_reset_color);
