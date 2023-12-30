#include "driver/tty.h"

char	term_get_c_entry_at(size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	return ((char)g_vga_buffer[index]);
}
