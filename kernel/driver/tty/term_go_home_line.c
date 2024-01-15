#include "driver/tty.h"

void	term_go_home_line(void)
{
	while (term_cursor_backward() == true) ;
}
EXPORT_SYMBOL(term_go_home_line);
