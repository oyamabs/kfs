/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnumbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 05:50:37 by tchampio          #+#    #+#             */
/*   Updated: 2026/10/22 21:26:36 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"

int	ft_print_integer(int i)
{
	int		size;
	char	str[32];

	ft_itoa_static(i, str, 32);
	size = ft_strlen(str);
	terminal_putstr(str);
	return (size);
}

static int	get_number_size(unsigned int i)
{
	int	size;

	if (i == 0)
		return (1);
	size = 0;
	while (i != 0)
	{
		i /= 10;
		size++;
	}
	return (size);
}

int	ft_print_uinteger(unsigned int i)
{
	unsigned int	nb;

	nb = i;
	if (nb >= 10)
	{
		terminal_putnbr(nb / 10);
		terminal_putnbr(nb % 10);
	}
	else
		terminal_putnbr('0' + nb);
	return (get_number_size(i));
}
