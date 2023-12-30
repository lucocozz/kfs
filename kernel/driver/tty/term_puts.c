#include "driver/tty.h"

void	term_puts(const char *str)
{
	term_write(str, strlen(str));
}
