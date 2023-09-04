/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:55:49 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/04 16:04:54 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	int		x;
	char	*str;

	x = -1;
	str = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (str == NULL)
		return (str);
	while (s1[++x] != 0)
		str[x] = s1[x];
	str[x] = 0;
	return (str);
}
