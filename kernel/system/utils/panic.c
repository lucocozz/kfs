#include "system/utils.h"

void panic(const char *msg)
{
	printk("KERNEL PANIC: %s\n", msg);
	ASM("cli; hlt");
}
EXPORT_SYMBOL(panic);
