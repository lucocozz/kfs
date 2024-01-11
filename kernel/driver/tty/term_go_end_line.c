#include "driver/tty.h"

void	term_go_end_line(void)
{
	while (term_get_c_entry_at() != '\0')
		term_cursor_forward();
}
