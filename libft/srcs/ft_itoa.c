/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:06:23 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/04 16:17:49 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	nbrlen(long int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	long int	k;
	int			i;
	char		*str;

	k = n;
	i = nbrlen(k);
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i] = 0;
	if (k < 0)
	{
		str[0] = '-';
		k = k * -1;
	}
	while (k >= 10)
	{
		str[i - 1] = (char)((k % 10) + '0');
		k = k / 10;
		i--;
	}
	str[i - 1] = ((char)(k + '0'));
	return (str);
}
