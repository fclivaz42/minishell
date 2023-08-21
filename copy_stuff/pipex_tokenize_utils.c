/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:54:59 by fclivaz           #+#    #+#             */
/*   Updated: 2023/04/11 18:55:06 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*first_token(char *src, int i)
{
	char	*token;

	token = (char *)ft_calloc(i + 1, sizeof(char));
	check_failed_memory(token);
	ft_strlcpy(token, src, i + 1);
	return (token);
}

int	skip_token(char *src, int i, char c)
{
	if (c == 34 || c == 39)
		while (!(src[i] == 34 || src[i] == 39))
			i++;
	else
		while (!(src[i] == ' ' || src[i] == 0))
			i++;
	while (src[i] == ' ' || src[i] == 0)
		i++;
	return (i);
}

static char	*quote_token(char *src, int i, char c)
{
	int		x;
	int		mem;
	char	*ret;

	mem = 0;
	++i;
	x = i;
	while (!(src[i] == c || src[i] == c))
	{
		++mem;
		++i;
	}
	ret = (char *)ft_calloc(mem + 1, sizeof(char));
	check_failed_memory(ret);
	i = 0;
	while (!(src[x] == c || src[x] == c))
	{
		ret[i] = src[x];
		++x;
		++i;
	}
	return (ret);
}

static char	*normal_token(char *src, int i)
{
	int		x;
	int		mem;
	char	*ret;

	mem = 0;
	x = i;
	while (!(src[i] == ' ' || src[i] == 0))
	{
		++mem;
		++i;
	}
	ret = (char *)ft_calloc(mem + 1, sizeof(char));
	check_failed_memory(ret);
	i = 0;
	while (!(src[x] == ' ' || src[x] == 0))
	{
		ret[i] = src[x];
		++x;
		++i;
	}
	return (ret);
}

char	*make_token(char *src, int i, char c)
{
	if (c == 34 || c == 39)
		return (quote_token(src, i, c));
	else
		return (normal_token(src, i));
}
