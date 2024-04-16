#include "driver/tty.h"

void	term_put_from_keyqueue(void)
{
	key_t key = keyboard_get_keypoll();
	if (key.code != 0)
		term_putkey(key);
}
EXPORT_SYMBOL(term_put_from_keyqueue);
