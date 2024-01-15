#include "driver/tty.h"

void	term_clear(void)
{
	uint8_t color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	uint16_t entry = vga_entry('\0', color);
	for (size_t i = 0; i < VGA_BUFFER_SIZE; ++i)
		g_vga_buffer[i] = entry;
	term_goto(0, 0);
	set_vga_cursor(0, 0);
}
EXPORT_SYMBOL(term_clear);
