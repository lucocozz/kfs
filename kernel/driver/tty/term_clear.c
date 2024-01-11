#include "driver/tty.h"

void	term_clear(void)
{
	uint8_t color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x)
			term_put_entry_at('\0', color, x, y);
	}
	set_vga_cursor(0, 0);
	term_goto(0, 0);
}
EXPORT_SYMBOL(term_clear);
