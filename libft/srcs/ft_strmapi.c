/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:59:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/04 16:11:03 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ret;

	i = -1;
	if (s == NULL)
		return (NULL);
	ret = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (s[++i] != 0)
		ret[i] = f(i, s[i]);
	ret[i] = 0;
	return (ret);
}
