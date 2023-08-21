/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:21:11 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/25 17:19:54 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	int				x;
	unsigned char	f;

	str = (char *)s;
	f = (unsigned char)c;
	x = ft_strlen(str) + 1;
	while (--x > 0)
		if (str[x] == f)
			return ((char *)str + x);
	if (str[x] == f)
		return ((char *)str + x);
	return (0);
}
