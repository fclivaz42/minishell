/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:58:05 by fclivaz           #+#    #+#             */
/*   Updated: 2023/11/21 21:11:32 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(long nbr, int fd)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		i += write(fd, "-", 1);
	nbr = nbr * -1;
	}
	if (nbr >= 10)
	{
		i += ft_putnbr_fd(nbr / 10, fd);
		nbr = nbr % 10;
	}
	if (nbr < 10)
		i += ft_putchar_fd(nbr + '0', fd);
	return (i);
}
