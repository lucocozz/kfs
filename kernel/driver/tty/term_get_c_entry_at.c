#include "driver/tty.h"

char	term_get_c_entry_at(void)
{
	const size_t index = term_get_index();
	return ((char)g_vga_buffer[index]);
}
EXPORT_SYMBOL(term_get_c_entry_at);
