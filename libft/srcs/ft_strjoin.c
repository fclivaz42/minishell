/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:39:59 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/25 13:52:37 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		diff;
	char	*ret;
	int		i;

	diff = -1;
	i = -1;
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ret == NULL)
		return (NULL);
	while (s1[++diff] != 0)
		ret[diff] = s1[diff];
	while (s2[++i] != 0)
		ret[diff + i] = s2[i];
	ret[diff + i] = 0;
	return (ret);
}
