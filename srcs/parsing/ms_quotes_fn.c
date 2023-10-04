/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_fn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:23:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/04 01:44:09 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_quotes(char *str, t_list *env, int *size, char q)
{
	int		s;
	int		x;
	char	c;
	char	*var;

	s = 0;
	x = 0;
	while (str[++x] != q)
	{
		if (str[x] == '$' && q == 34)
		{
			var = &str[x];
			while (!(str[x] == ' ' || str[x] == 34))
				++x;
			c = str[x];
			str[x] = 0;
			s = s + ft_strlen(find_env(env, (var + 1)));
			str[x] = c;
		}
		++s;
		++x;
	}
	*size = *size + s - 1;
	return (x);
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
