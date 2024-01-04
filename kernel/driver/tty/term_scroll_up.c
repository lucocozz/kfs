#include "driver/tty.h"

void	term_scroll_up(void)
{
	memmove(g_vga_buffer, g_vga_buffer + VGA_WIDTH, sizeof(uint16_t) * (VGA_BUFFER_SIZE - VGA_WIDTH));
	for (size_t x = 0; x < VGA_WIDTH; ++x)
		term_put_c_entry_at('\0', x, VGA_HEIGHT - 1);
}
