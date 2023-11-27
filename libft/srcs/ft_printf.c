/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:26 by fclivaz           #+#    #+#             */
/*   Updated: 2023/11/22 17:12:45 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	print_hex(unsigned long int ptdr, char str, int *i, int mode)
{
	if (str == 'x' || str == 'X')
		ptdr = (unsigned int)ptdr;
	if (mode)
		*i += write(1, "0x", 2);
	if (ptdr >= 16)
	{
		print_hex(ptdr / 16, str, i, 0);
		print_hex(ptdr % 16, str, i, 0);
	}
	else
	{
		if (ptdr <= 9)
			*i += ft_putchar_fd((ptdr + '0'), 1);
		else
		{
			if (str == 'x' || str == 'p')
				*i += ft_putchar_fd((ptdr - 10 + 'a'), 1);
			if (str == 'X')
				*i += ft_putchar_fd((ptdr - 10 + 'A'), 1);
		}
	}
}

static void	check_format(va_list ap, const char str, int *i)
{
	char	*s;

	if (str == 's')
	{
		s = va_arg(ap, char *);
		if (s == NULL)
		{
			*i += write(1, "(null)", 6);
			return ;
		}
		*i += ft_putstr_fd(s, 1);
	}
	else if (str == 'c')
		*i += ft_putchar_fd(va_arg(ap, int), 1);
	else if (str == 'i' || str == 'd')
		*i += ft_putnbr_fd(va_arg(ap, int), 1);
	else if (str == 'u')
		*i += ft_putnbr_fd(va_arg(ap, unsigned int), 1);
	else if (str == 'x' || str == 'X')
		print_hex(va_arg(ap, int), str, i, 0);
	else if (str == 'p')
		print_hex(va_arg(ap, uintptr_t), str, i, 1);
	else if (str == '%')
		*i += write(1, "%", 1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	ap;

	i = 0;
	va_start(ap, str);
	while (*str != '\0')
	{
		if (*str != '%')
			i += ft_putchar_fd(*str, 1);
		if (*str == '%')
		{		
			check_format(ap, str[1], &i);
		++str;
		}
	++str;
	}
	va_end(ap);
	return (i);
}
