#include "driver/tty.h"

void	term_goto(size_t x, size_t y)
{
	g_tty[g_tty_index].column = x;
	g_tty[g_tty_index].row = y;
}
