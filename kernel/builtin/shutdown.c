#include "builtin.h"
#include "driver/serials.h"

void	shutdown(void)
{
	halt();
	outb(0X64, 0xFE);
}
EXPORT_SYMBOL(shutdown);