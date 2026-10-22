/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 05:52:06 by tchampio          #+#    #+#             */
/*   Updated: 2026/10/22 20:33:14 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_print_ptr_nb(uintptr_t decimal_number)
{
	long		i;
	long		j;
	uintptr_t	temp;
	char		hexa_number[100];

	i = 1;
	while (decimal_number != 0)
	{
		temp = decimal_number % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 55;
		hexa_number[i++] = temp;
		decimal_number = decimal_number / 16;
	}
	j = i - 1;
	while (j > 0)
	{
		terminal_putchar(ft_tolower(hexa_number[j--]));
	}
	return (i - 1);
}

int	ft_print_ptr(void *ptr)
{
	int			size;
	uintptr_t	addr;

	if (ptr == NULL)
	{
		terminal_putstr("(nil)");
		return (5);
	}
	addr = (uintptr_t)ptr;
	terminal_putstr("0x");
	size = ft_print_ptr_nb(addr) + 2;
	return (size);
}
