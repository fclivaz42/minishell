/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/05 19:53:43 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

int	expand_var(char *str, t_list *env, int *size)
{
	int		x;
	char	c;
	char	*var;

	x = 0;
	++str;
	var = str;
	while (ft_isalnum(str[x]) || str[x] == '?')
		++x;
	c = str[x];
	str[x] = 0;
	if (find_env(env, var))
		*size = *size + ft_strlen(find_env(env, var)) - 1;
	str[x] = c;
	return (x);
}

static int	find_size(char *str, t_list *env)
{
	int		size;

	size = 0;
	while (!(ft_strchr("<|> \t\n\0", *str)))
	{
		if (*str == 34 || *str == 39)
			str = str + count_quotes(str, env, &size, *str);
		else if (*str == '$')
			str = str + expand_var(str, env, &size);
		if (ft_strchr("<|> \t\n\0", *str))
			return (size);
		++size;
		++str;
	}
	return (size + 1);
}

static char	*interpret(char *str, int *delta, t_list *env)
{
	char	*ntrp;
	char	*d;
	int		x;

	x = 0;
	d = str;
	ntrp = (char *)memchk(ft_calloc(find_size(str, env), sizeof(char)));
	while (!(ft_strchr("<|> \t\n\0", *str)))
	{
		if (*str == 34 || *str == 39)
			str = str + copy_quotes(&ntrp[x], str, env, *str);
		else if (*str == '$')
			str = str + copy_var(&ntrp[x], str, env);
		else
		{
			ntrp[x] = str[0];
			++str;
		}
		while (ntrp[x] != 0)
			++x;
	}
	*delta = (char *)str - (char *)d;
	return (ntrp);
}

t_list	*interparse(char *rl, t_list *env)
{
	t_list	*list;
	int		x;
	int		delta;

	x = 0;
	while (*rl != 0)
	{
		while (ft_strchr(" \t\n", *rl))
			++rl;
		if (x == 0)
			list = memchk(ft_lstnew(interpret(rl, &delta, env)));
		if (x > 0)
			ft_lstadd_back(&list, memchk(\
				ft_lstnew(interpret(rl, &delta, env))));
		++x;
		rl = rl + delta;
	}
	return (list);
}
