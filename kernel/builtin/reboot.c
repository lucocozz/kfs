#include "driver/serials.h"

void	reboot(void)
{
	outb(KEYBOARD_PORT_STATUS, 0xFE);
}
EXPORT_SYMBOL(reboot);