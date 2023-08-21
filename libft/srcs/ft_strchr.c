/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:21:11 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/25 17:13:30 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	x;

	str = (char *)s;
	x = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == x)
			return (str);
		str++;
	}
	if (*str == x)
		return (str);
	return (0);
}
