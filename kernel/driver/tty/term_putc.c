#include "driver/tty.h"

void	term_putc(char c)
{
	term_write(&c, 1);
}
