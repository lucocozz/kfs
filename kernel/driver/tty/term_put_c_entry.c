#include "driver/tty.h"

void	term_put_c_entry(char c)
{
	term_put_entry(c, g_tty[g_tty_index].color);
}
