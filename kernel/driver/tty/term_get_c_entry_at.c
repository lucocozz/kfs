#include "driver/tty.h"

char	term_get_c_entry_at(void)
{
	const size_t index = g_tty[g_tty_index].row * VGA_WIDTH + g_tty[g_tty_index].column;
	return ((char)g_vga_buffer[index]);
}
