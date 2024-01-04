#include "printk.h"

static void	__rigth_padding(printk_flags_t flags, char *nb_str, int nb)
{
	int	len = strlen(nb_str);

	if (nb < 0)
		printk_putc(&flags, '-');
	while (flags.precision > len) {
		printk_putc(&flags, '0');
		flags.precision--;
	}
	if (nb == 0 && flags.precision == 0 && flags.width != 0)
		printk_putc(&flags, ' ');
	else if (nb == 0 || flags.precision != 0)
		printk_puts(&flags, nb_str);
	while (flags.width > 0)
		printk_putc(&flags, ' ');
}

static void	__left_padding(printk_flags_t flags, char *nb_str, int nb)
{
	int	len = strlen(nb_str);

	if (nb < 0 && flags.fill == '0')
		printk_write('-');
	while (flags.width > len && flags.width > flags.precision) {
		if (nb < 0 && (flags.width == len + 1 || flags.width == flags.precision + 1))
			break ;
		printk_putc(&flags, flags.fill);
	}
	if (nb < 0 && flags.fill == ' ')
		printk_write('-');
	else if (nb < 0 && flags.precision > len)
		printk_putc(&flags, '0');
	while (flags.precision > len) {
		printk_putc(&flags, '0');
		flags.precision--;
	}
	if (nb == 0 && flags.precision == 0 && flags.width != 0)
		printk_putc(&flags, ' ');
	else if (nb != 0 || flags.precision != 0) {
		printk_puts(&flags, nb_str);
	}
}

void	printk_format_d(va_list *ap, printk_flags_t flags)
{
	int		nb = va_arg(*ap, int);
	char	nb_str[12] = {0};

	itoa((nb < 0) ? nb * -1 : nb, nb_str, 10);
	if (flags.padding != 0)
		__rigth_padding(flags, nb_str, nb);
	else
		__left_padding(flags, nb_str, nb);
}

void	printk_format_i(va_list *ap, printk_flags_t flags)
{
	printk_format_d(ap, flags);
}
