/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_toolbox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:09:35 by fclivaz           #+#    #+#             */
/*   Updated: 2022/11/24 21:03:48 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_string(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != 0)
		ft_putchar_fd(str[i++], 1);
	return (i);
}

int	print_nbr(int arg)
{
	int				i;
	long long int	nbr;

	if (arg == 0)
		return (write(1, "0", 1));
	i = 0;
	nbr = arg;
	ft_putnbr_fd(arg, 1);
	if (nbr < 0)
	{
		nbr = nbr * -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

int	print_unsigned(unsigned int arg)
{
	int				i;
	unsigned int	len;

	i = 0;
	if (arg == 0)
		return (write(1, "0", 1));
	len = arg;
	if (arg >= 10)
	{
		print_unsigned(arg / 10);
		arg = arg % 10;
	}
	if (arg < 10)
	{
		arg = arg + '0';
		write(1, &arg, 1);
	}
	while (len > 0)
	{
		len /= 10;
	i++;
	}
	return (i);
}

static void	actual_addr(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		actual_addr(ptr / 16);
		actual_addr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

int	print_addr(uintptr_t ptr)
{
	int	i;

	i = write(1, "0x", 2);
	if (ptr == 0)
		return (i += write(1, "0", 1));
	actual_addr(ptr);
	while (ptr != 0)
	{
		i++;
		ptr = ptr / 16;
	}
	return (i);
}
