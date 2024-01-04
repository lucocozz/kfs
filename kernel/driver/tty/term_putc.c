#include "driver/tty.h"
#include "ctype.h"

void	term_putc(char c)
{
	if (isprint(c) == true && term_get_c_entry_at(g_tty[g_tty_index].column, g_tty[g_tty_index].row) != '\0') {
		size_t len = 0;
		size_t index = term_get_index();
		void *src = g_vga_buffer + term_get_index();
		void *dest = g_vga_buffer + term_get_index() + 1;
		while (g_vga_buffer[index + len] != '\0')
			++len;
		memmove(dest, src, len);
	}
	term_write(&c, 1);
}
