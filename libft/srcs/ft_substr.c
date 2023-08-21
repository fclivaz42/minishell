/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:57:27 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/28 18:29:11 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	j;
	size_t	size;

	size = ft_strlen(s);
	if (size <= start)
		return (ft_calloc(1, 1));
	if (size - start < len)
		len = size - start;
	ret = (char *)ft_calloc(sizeof(char), len + 1);
	if (ret == NULL)
		return (NULL);
	j = 0;
	while (j < len && s[start] != 0)
		ret[j++] = s[start++];
	ret[j] = 0;
	return (ret);
}
