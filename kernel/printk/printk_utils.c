/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:41:25 by lucocozz          #+#    #+#             */
/*   Updated: 2023/12/31 19:58:17 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"

void	ft_print_buffer(t_buffer *buffer)
{
	write(buffer->fd, buffer->data, buffer->i);
	buffer->len += buffer->i;
	ft_bzero(buffer->data, VFPRINTF_BUFFER_SIZE);
	buffer->i = 0;
}

void	ft_insert_in_buffer(t_buffer *buffer, char c)
{
	buffer->data[buffer->i++] = c;
	if (buffer->i == VFPRINTF_BUFFER_SIZE - 1)
		ft_print_buffer(buffer);
}

void	ft_insert_format(t_buffer *buffer, t_printf *data, char c)
{
	ft_insert_in_buffer(buffer, c);
	data->width--;
}

void	ft_insert_str(t_buffer *buffer, t_printf *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_insert_format(buffer, data, str[i++]);
}
