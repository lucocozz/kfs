#include "driver/tty.h"

void	term_put_entry(char c, uint8_t color)
{
	term_put_entry_at(c, color, g_tty[g_tty_index].column, g_tty[g_tty_index].row);
}
