/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:39:53 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/25 18:33:46 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		x;
	size_t	i;
	char	*str1;
	char	*str2;

	x = 0;
	i = 0;
	if (n == 0)
		return (0);
	n = n - 1;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while ((unsigned char)str1[i] == (unsigned char)str2[i] && i < n)
	{
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
