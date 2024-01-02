/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:36:30 by lucocozz          #+#    #+#             */
/*   Updated: 2023/12/31 20:08:25 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"

int	parse_padding(char c, printk_flags_t *flags)
{
	flags->padding = (c == '-' ? 1 : 0);
	if (flags->padding == 1)
		flags->fill = ' ';
	return (flags->padding);
}


int	parse_fill(char c, printk_flags_t *flags)
{
	if (c == '0' && flags->precision == -1)
		flags->fill = '0';
	else
		flags->fill = ' ';
	return (c == '0');
}

int	parse_width(const char *s, printk_flags_t *flags, va_list ap)
{
	int	i = 0;
	int	nb = 0;

	if (s[i] == '*')
	{
		flags->width = va_arg(ap, int);
		if (flags->width < 0)
		{
			flags->width *= -1;
			parse_padding('-', flags);
		}
		i++;
	}
	else
	{
		nb = atoi(s);
		if (nb < 0)
			flags->width = nb * -1;
		else
			flags->width = nb;
		while (isdigit(s[i]))
			i++;
	}
	return (i);
}

int	parse_precision(const char *s, printk_flags_t *flags, va_list ap)
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
			flags->precision = atoui(&s[i]);
		if (flags->precision < 0 && flags->fill == '0')
			flags->fill = '0';
		else
			flags->fill = ' ';
		while (isdigit(s[i]))
			i++;
	}
	return (i);
}
