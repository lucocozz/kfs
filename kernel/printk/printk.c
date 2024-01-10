#include "printk.h"

printk_buffer_t		g_printk_buffer = PRINTK_BUFFER_INIT;

static void	__call_formater(printk_flags_t flags, va_list *ap)
{
	void (*formaters[])(va_list *ap, printk_flags_t flags) = {
		['%'] = &printk_format_per, ['c'] = &printk_format_c, ['s'] = &printk_format_s,
		['p'] = &printk_format_p,   ['d'] = &printk_format_d, ['i'] = &printk_format_i,
		['u'] = &printk_format_u,   ['x'] = &printk_format_x, ['X'] = &printk_format_xu
	};

	if (flags.type != '\0' && formaters[(int)flags.type] != NULL)
		formaters[(int)flags.type](ap, flags);
}

static printk_flags_t	__parse_flags(const char *format, int *i, va_list *ap)
{
	printk_flags_t	flags = PRINTK_FLAGS_INIT;

	*i += 1;
	while (format[*i] != '\0' && strchr(PRINTK_FORMATS_TYPE, format[*i]) == NULL)
	{
		*i += printk_parse_padding(format[*i], &flags);
		*i += printk_parse_fill(format[*i], &flags);
		*i += printk_parse_width(&format[*i], &flags, ap);
		*i += printk_parse_precision(&format[*i], &flags, ap);
	}
	flags.type = format[*i];
	if (format[*i] != '\0')
		*i += 1;
	return (flags);
}

int	printk(const char *format, ...)
{
	va_list		ap;
	int			i = 0;

	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			__call_formater(__parse_flags(format, &i, &ap), &ap);
		else
			printk_write(&format[i++], 1);
	}
	printk_print_buffer();
	return (g_printk_buffer.len);
}
EXPORT_SYMBOL(printk)
