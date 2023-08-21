/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:22:29 by fclivaz           #+#    #+#             */
/*   Updated: 2023/04/01 19:22:38 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	skip_quotes(char *src, int amount, int i, int chr)
{
	++i;
	while (src[i] != chr)
	{
		if (src[i] == 0)
			error_bad_format(src);
		if (src[i] == 92)
			++i;
	++i;
	}
	amount++;
	return (i);
}

static int	token_amount(char *src)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (!(src[i] == ' ' || src[i] == 0))
		i++;
	i--;
	while (src[++i] != 0)
	{
		if (src[i] == 92)
			i = i + 2;
		if (src[i] == 34 || src[i] == 39)
			i = skip_quotes(src, amount, i, src[i]);
		if (src[i] == ' ')
		{
			while (src[i + 1] == ' ')
				i++;
			if (src[i + 1] != 0)
				++amount;
		}
	}
	++amount;
	return (amount);
}

static char	*token_char(char *src, int y)
{
	int		i;
	int		x;

	i = 0;
	x = 1;
	while (!(src[i] == ' ' || src[i] == 0))
		i++;
	if (y == 0)
		return (first_token(src, i));
	while (src[i] == ' ' || src[i] == 0)
		i++;
	while (x < y)
	{
		i = skip_token(src, i, src[i]);
		++x;
	}
	return (make_token(src, i, src[i]));
}

char	**tokenize(char *src)
{
	char	**tokens;
	int		x;
	int		y;

	y = -1;
	x = token_amount(src);
	tokens = (char **)ft_calloc(x + 1, sizeof(char **));
	check_failed_memory(tokens);
	while (++y != x)
		tokens[y] = token_char(src, y);
	return (tokens);
}
