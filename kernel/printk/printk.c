/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:53:30 by lucocozz          #+#    #+#             */
/*   Updated: 2023/12/31 20:00:14 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"

printk_buffer_t	g_printk_buffer = PRINTK_BUFFER_INIT;

static void	__call_formater(printk_flags_t flags, va_list ap)
{
	void (*formats[])(va_list ap, printk_flags_t flags) = {
		['%'] = &format_per, ['c'] = &format_c, ['s'] = &format_s,
		['p'] = &format_p,   ['d'] = &format_d, ['i'] = &format_i,
		['u'] = &format_u,   ['x'] = &format_x, ['X'] = &format_xu
	};

	if (formats[(int)flags.type] != NULL)
		formats[(int)flags.type](ap, flags);
}

static printk_flags_t	__parse_flags(const char *format, int *i, va_list ap)
{
	printk_flags_t	flags = PRINTK_FLAGS_INIT;

	*i += 1;
	while (!strchr(PRINTK_FORMATS_TYPE, format[*i]) && format[*i])
	{
		*i += parse_padding(format[*i], &flags);
		*i += parse_fill(format[*i], &flags);
		*i += parse_width(&format[*i], &flags, ap);
		*i += parse_precision(&format[*i], &flags, ap);
	}
	flags.type = format[*i];
	*i += 1;
	return (flags);
}

int	printk(const char *format, ...)
{
	int			i = 0;
	va_list		ap;

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			__call_formater(__parse_flags(format, &i, ap), ap);
		else
			insert_in_buffer(format[i++]);
	}
	print_buffer();
	return (printk_buffer.len);
}
