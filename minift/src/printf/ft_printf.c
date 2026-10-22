/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:01:45 by tchampio          #+#    #+#             */
/*   Updated: 2024/11/04 15:28:21 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_print_string(char *s)
{
	int	size;

	if (!s)
	{
		terminal_putstr("(null)");
		return (6);
	}
	size = (int)ft_strlen(s);
	terminal_putstr(s);
	return (size);
}

static int	ft_check_flag(char flag, va_list args)
{
	int	added;

	added = 0;
	if (flag == 'c')
		return (terminal_putchar(va_arg(args, int)), 1);
	else if (flag == 's')
		added += ft_print_string((char *)va_arg(args, char *));
	else if (flag == 'p')
		added += ft_print_ptr((void *)va_arg(args, void *));
	else if (flag == 'i' || flag == 'd')
		added += ft_print_integer((int)va_arg(args, int));
	else if (flag == 'u')
		added += ft_print_uinteger((unsigned int)va_arg(args, unsigned int));
	else if (flag == 'x')
		added += ft_print_hex((int)va_arg(args, int), 'x');
	else if (flag == 'X')
		added += ft_print_hex((int)va_arg(args, int), 'X');
	else if (flag == '%')
		return (terminal_putchar('%'), 1);
	return (added);
}

int	ft_printf(const char *format, ...)
{
	int		counter;
	va_list	args;
	size_t	index;

	index = 0;
	counter = 0;
	va_start(args, format);
	while (format[index])
	{
		if (format[index] == '%')
		{
			index++;
			counter += ft_check_flag(format[index], args);
			index++;
		}
		else
		{
			terminal_putchar(format[index]);
			counter++;
			index++;
		}
	}
	return (counter);
}
