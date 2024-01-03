#include "driver/tty.h"

void	term_putnbr(int nb, int base)
{
	char	nb_str[12] = {0};

	itoa(nb, nb_str, base);
	term_puts(nb_str);
}