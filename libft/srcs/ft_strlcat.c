/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:20:11 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/25 16:47:34 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s1;
	size_t	s2;

	s2 = 0;
	while (dst[s2] != 0 && s2 < size)
		s2++;
	s1 = s2;
	while (src[s2 - s1] && s2 + 1 < size)
	{
		dst[s2] = src[s2 - s1];
		s2++;
	}
	if (s1 < s2)
		dst[s2] = 0;
	return (s1 + ft_strlen(src));
}
