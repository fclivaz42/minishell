/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_fn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:23:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/03 20:25:04 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_dquotes(char *str, t_list *env)
{
	int		size;
	char	c;
	char	*var;

	size = 0;
	++str;
	while (*str != 34)
	{
		if (*str == '$')
		{
			var = str;
			while (!(*str == ' ' || *str == 34))
				++str;
			c = str[0];
			str[0] = 0;
			size = size + ft_strlen(find_env(env, (var + 1)));
			str[0] = c;
		}
		if (*str == 34)
			return (size);
		++size;
		++str;
	}
	return (size);
}

int	count_squotes(char *str)
{
	int	size;

	size = 0;
	++str;
	while (str[size] != 39)
		++size;
	return (size);
}

int	copy_quotes(char *ntrp, char *str, t_list *env, char c)
{
	int	x;

	x = -1;
	++str;
	if (c == 34)
	{
	}
	else
	{
		while (str[++x] != 39)
			ntrp[x] = str[x];
	}
	return (x + 1);
}
