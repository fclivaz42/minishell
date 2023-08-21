/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:14:33 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/25 20:52:16 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *hstk, const char *ndl, size_t len)
{
	size_t	i;
	int		y;

	y = 0;
	i = -1;
	if (ndl[0] == 0)
		return ((char *)hstk);
	while (hstk[++i] != 0 && i != len)
	{
		if (hstk[i] == ndl[0])
		{
			while (hstk[i + y] == ndl[y] && ndl[y] != 0 && i + y < len)
			{
				if (ndl[y + 1] == 0)
					return ((char *)&hstk[i]);
				y++;
			}
		}
	}
	return (NULL);
}
