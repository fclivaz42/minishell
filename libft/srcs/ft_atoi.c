/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:49:14 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/17 16:57:57 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	x;
	int	neg;
	int	nbr;

	neg = 1;
	nbr = 0;
	x = 0;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == 32)
		++x;
	if (nptr[x] == '-')
		neg = neg * -1;
	if (nptr[x] == '-' || nptr[x] == '+')
		++x;
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		nbr = (nbr * 10) + (nptr[x] - '0');
		++x;
	}	
	return (nbr * neg);
}
