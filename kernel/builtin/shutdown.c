#include "builtin.h"
#include "driver/serials.h"

void	shutdown(void)
{
	// halt();
	outw(0x604, 0x2000);
}
EXPORT_SYMBOL(shutdown);