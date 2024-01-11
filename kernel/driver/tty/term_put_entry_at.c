#include "driver/tty.h"

void	term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	g_vga_buffer[index] = vga_entry(c, color);
}
EXPORT_SYMBOL(term_put_entry_at);
