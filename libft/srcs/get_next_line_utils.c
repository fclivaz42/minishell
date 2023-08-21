/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:54 by fclivaz           #+#    #+#             */
/*   Updated: 2023/02/15 20:59:49 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_gnllen(const char *s)
{
	int		x;

	if (!s)
		return (0);
	x = 0;
	while (s[x] != 0)
		x++;
	return (x);
}

char	*ft_gnlchr(const char *s, int c)
{
	char			*str;
	unsigned char	x;

	if (!s)
		return (0);
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

char	*ft_gnljoin(char *s1, char *s2)
{
	int		i;
	int		diff;
	char	*ret;

	i = -1;
	diff = -1;
	if (s1 == NULL)
		s1 = (char *)ft_calloc(1, 1);
	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ret = (char *)ft_calloc((ft_gnllen(s1) + ft_gnllen(s2) + 1), sizeof(char));
	while (s1[++diff] != 0)
		ret[diff] = s1[diff];
	while (s2[++i] != 0)
		ret[diff + i] = s2[i];
	ret[diff + i] = 0;
	free(s1);
	return (ret);
}
