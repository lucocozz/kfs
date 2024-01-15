#include "driver/tty.h"

bool	term_cursor_backward(void)
{
	size_t index = term_get_index();

	if (index == 0 || (char)g_vga_buffer[index - 1] == '\0')
		return (false);
	term_set_index(index - 1);
	return (true);
}
EXPORT_SYMBOL(term_cursor_backward);