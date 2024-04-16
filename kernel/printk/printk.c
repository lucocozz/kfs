#include "printk.h"

int printk(const char *format, ...)
{
	va_list ap;
	size_t	size;

	va_start(ap, format);
	size = vprintk(format, ap);
	va_end(ap);

	return (size);
}
EXPORT_SYMBOL(printk);