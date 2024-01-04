#include "printk.h"

static void	__rigth_padding(printk_flags_t flags, char *nb_str, int nb)
{
	int	len = strlen(nb_str);

	while (flags.precision > len) {
		printk_putc(&flags, '0');
		flags.precision--;
	}
	if (nb == 0 && flags.precision == 0 && flags.width != 0)
		printk_putc(&flags, ' ');
	else if (nb != 0 || flags.precision != 0)
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
	if (nb == 0 && flags.precision == 0 && flags.width != 0)
		printk_putc(&flags, ' ');
	else if (nb == 0 || flags.precision != 0)
		printk_puts(&flags, nb_str);
}

void	printk_format_u(va_list ap, printk_flags_t flags)
{
	unsigned int	nb = va_arg(ap, unsigned int);
	char			nb_str[32];

	utoa(nb, nb_str, 10);
	if (flags.padding)
		__rigth_padding(flags, nb_str, nb);
	else
		__left_padding(flags, nb_str, nb);
}

void	printk_format_per(va_list ap, printk_flags_t flags)
{
	(void)ap;
	(void)flags;
	printk_write('%');
}
