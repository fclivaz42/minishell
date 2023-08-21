/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:42:29 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/31 17:51:39 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*splitter(char *str, char c)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i] != 0)
		if (str[i] == c)
			break ;
	ret = (char *)ft_calloc(i + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] == c)
			break ;
		ret[i] = str[i];
	}
	ret[i] = 0;
	return (ret);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	words;
	int	bingo;

	i = -1;
	words = 0;
	bingo = 0;
	while (str[++i] != 0)
	{
		if (str[i] != c && bingo == 0)
		{
			words++;
			bingo = 1;
		}
		else if (str[i] == c)
			bingo = 0;
	}	
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	char	*str;
	size_t	word;
	size_t	x;

	x = -1;
	str = (char *)s;
	word = count_words(s, c);
	array = (char **)ft_calloc((word + 1), sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (word-- != 0)
	{
		while (*str == c)
			str++;
		array[++x] = splitter(str, c);
		if (array[x] == NULL)
			return (NULL);
		while (*str++ != c)
			if (*str == 0)
				break ;
	}
	return (array);
}
