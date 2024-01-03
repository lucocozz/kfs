#include "printk.h"
#include "ctype.h"
#include "stdlib.h"

int	printk_parse_padding(char c, printk_flags_t *flags)
{
	flags->padding = (c == '-' ? 1 : 0);
	if (flags->padding == 1)
		flags->fill = ' ';
	return (flags->padding);
}


int	printk_parse_fill(char c, printk_flags_t *flags)
{
	if (c == '0' && flags->precision == -1)
		flags->fill = '0';
	else
		flags->fill = ' ';
	return (c == '0');
}

int	printk_parse_width(const char *str, printk_flags_t *flags, va_list ap)
{
	int	i = 0;

	if (str[i] == '*')
	{
		flags->width = va_arg(ap, int);
		if (flags->width < 0) {
			flags->width *= -1;
			printk_parse_padding('-', flags);
		}
		i++;
	}
	else
	{
		int nb = atoi(str);
		flags->width = (nb < 0 ? nb * -1 : nb);
		while (isdigit(str[i]) == true)
			i++;
	}
	return (i);
}

int	printk_parse_precision(const char *s, printk_flags_t *flags, va_list ap)
{
	int	i;

	i = 0;
	if (s[i] == '.')
	{
		i++;
		if (s[i] == '*')
		{
			flags->precision = va_arg(ap, int);
			if (flags->precision < 0)
				flags->precision = -1;
			i++;
		}
		else
			flags->precision = atoi(&s[i]);
		if (flags->precision < 0 && flags->fill == '0')
			flags->fill = '0';
		else
			flags->fill = ' ';
		while (isdigit(s[i]))
			i++;
	}
	return (i);
}
