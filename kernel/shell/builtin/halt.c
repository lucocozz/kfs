#include "driver/serials.h"

void	halt(void)
{
	ASM("cli");
	ASM("hlt");
}
EXPORT_SYMBOL(halt);
