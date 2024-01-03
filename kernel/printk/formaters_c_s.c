#include "printk.h"

static void	__rigth_padding(printk_flags_t flags, char *str)
{
	int	i = 0;

	if (flags.precision == -1) {
		while (str[i] != '\0')
			printk_putc(&flags, str[i++]);
	}
	else {
		while (str[i] != '\0' && flags.precision-- > 0)
			printk_putc(&flags, str[i++]);
	}
	while (flags.width > 0)
		printk_putc(&flags, ' ');
}

static void	__left_padding(printk_flags_t flags, char *str)
{
	int	i = 0;
	int	len = strlen(str);

	len = (len < flags.precision) ? len : flags.precision;
	while (flags.width > len)
		printk_putc(&flags, flags.fill);
	while (len-- > 0)
		printk_write(str[i++]);
}

void	printk_format_s(va_list ap, printk_flags_t flags)
{
	char	*str = va_arg(ap, char*);

	if (str == NULL)
		str = "(null)";
	if (flags.padding != 0)
		__rigth_padding(flags, str);
	else
		__left_padding(flags, str);
}

void	printk_format_c(va_list ap, printk_flags_t flags)
{
	char c = (char)va_arg(ap, int);

	if (flags.padding != 0) {
		printk_putc(&flags, c);
		while (flags.width > 0)
			printk_putc(&flags, ' ');
	}
	else {
		while (flags.width > 1)
			printk_putc(&flags, flags.fill);
		printk_putc(&flags, c);
	}
}
