#include "driver/tty.h"

size_t	term_get_index(void)
{
	return (g_tty[g_tty_index].row * VGA_WIDTH + g_tty[g_tty_index].column);
}
EXPORT_SYMBOL(term_get_index);
