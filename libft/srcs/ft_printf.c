/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:26 by fclivaz           #+#    #+#             */
/*   Updated: 2022/11/24 21:03:43 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	print_int(char str, int arg)
{
	int	i;

	i = 0;
	if (str == 'c')
	{
		ft_putchar_fd(arg, 1);
	i++;
	}
	if (str == 'i' || str == 'd')
		i = print_nbr(arg);
	return (i);
}

static int	check_format(va_list ap, const char str)
{
	int		i;

	i = 0;
	if (str == '%')
	{
		i += write(1, "%", 1);
	}
	if (ft_strchr("cid", str) != NULL)
		i = print_int(str, va_arg(ap, int));
	if (str == 'u')
		i = print_unsigned(va_arg(ap, unsigned int));
	if (str == 'x' || str == 'X')
		i = print_hex(str, va_arg(ap, int));
	if (str == 'p')
		i = print_addr(va_arg(ap, uintptr_t));
	if (str == 's')
		i = print_string(va_arg(ap, char *));
	return (i);
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
		{
			ft_putchar_fd(*str, 1);
		i++;
		}
		if (*str == '%')
		{		
			i = i + check_format(ap, str[1]);
		str++;
		}
	str++;
	}
	va_end(ap);
	return (i);
}
