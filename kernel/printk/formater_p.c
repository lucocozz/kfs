#include "printk.h"

static void	__rigth_padding(printk_flags_t flags, char *nb_str, int nb)
{
	int	len = strlen(nb_str);

	while (flags.precision > len) {
		printk_putc(&flags, '0');
		flags.precision--;
	}
	if (nb != 0 || flags.precision != 0 || flags.width == 0)
		printk_puts(&flags, nb_str);
	while (flags.width > 0)
		printk_putc(&flags, ' ');
}

static void	__left_padding(printk_flags_t flags, char *nb_str, int nb)
{
	int	len = strlen(nb_str);

	while (flags.width > len && flags.width > flags.precision)
		printk_putc(&flags, flags.fill);
	while (flags.precision > len) {
		printk_putc(&flags, '0');
		flags.precision--;
	}
	if (nb != 0 || flags.precision != 0 || flags.width == 0)
		printk_puts(&flags, nb_str);
}

void	printk_format_p(va_list *ap, printk_flags_t flags)
{
	uintptr_t	nb = (uintptr_t)va_arg(*ap, void *);
	char		nb_str[34] = {0};

	utoa(nb, nb_str, 16);
	printk_write("0x", 2);
	if (flags.padding != 0)
		__rigth_padding(flags, nb_str, nb);
	else
		__left_padding(flags, nb_str, nb);
}
