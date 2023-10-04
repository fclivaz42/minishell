/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/04 03:32:03 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	expand_var(char *str, t_list *env, int *size)
{
	int		x;
	char	c;
	char	*var;

	x = 0;
	++str;
	var = str;
	while (ft_isalnum(str[x]))
		++x;
	c = str[x];
	str[x] = 0;
	*size = *size + ft_strlen(find_env(env, var));
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

static char	*interpret(char *str, t_list *env)
{
	char	*ntrp;
	char	c;
	int		x;

	ntrp = (char *)memchk(ft_calloc(find_size(str, env), sizeof(char)));
	while (!(ft_strchr("<|> \t\n\0", *str)))
	{
		if (ft_strchr("{}[]()\\;%~`?!#", *str))
		{
			zerofree(ntrp);
			return (error_unsupported_character(*str));
		}
		else if (*str == 34 || *str == 39)
			str = str + copy_quotes(&ntrp[x], str, env, *str);
	}
	return (ntrp);
}

t_list	*interparse(char *rl, t_list *env)
{
	t_list	*list;
	int		x;

	x = 0;
	while (*rl != 0)
	{
		while (ft_strchr(" \t\n", *rl))
			++rl;
		if (x == 0)
			list = memchk(ft_lstnew(interpret(rl, env)));
		if (x > 0)
			ft_lstadd_back(&list, memchk(ft_lstnew(interpret(rl, env))));
		++x;
	}
	return (list);
}