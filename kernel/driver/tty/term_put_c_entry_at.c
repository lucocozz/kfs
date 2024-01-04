#include "driver/tty.h"

void	term_put_c_entry_at(char c, size_t x, size_t y)
{
	term_put_entry_at(c, g_tty[g_tty_index].color, x, y);
}
