/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 21:30:11 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static char	*redirections(char *str, size_t *delta)
{
	char	*rdr;

	if (!ft_strncmp(str, "<<", 2))
		rdr = (char *)memchk(ft_strdup("<<"));
	else if (!ft_strncmp(str, ">>", 2))
		rdr = (char *)memchk(ft_strdup(">>"));
	else if (!ft_strncmp(str, "|", 1))
		rdr = (char *)memchk(ft_strdup("|"));
	else if (!ft_strncmp(str, "<", 1))
		rdr = (char *)memchk(ft_strdup("<"));
	else if (!ft_strncmp(str, ">", 1))
		rdr = (char *)memchk(ft_strdup(">"));
	else
		rdr = NULL;
	*delta = *delta + ft_strlen(rdr);
	return (rdr);
}

static char	*interpret(char *str, size_t *delta, t_list *env)
{
	char	*ntrp;
	char	*d;
	int		x;

	x = 0;
	if (ft_strchr("<|>", *str))
		return (redirections(str, delta));
	d = str;
	ntrp = (char *)memchk(ft_calloc(find_size(str, env), sizeof(char)));
	while (!(ft_strchr("<|> \t\n\0", *str)))
	{
		if (*str == 34 || *str == 39)
			str = str + copy_quotes(&ntrp[x], str, env, *str);
		else if (*str == '$')
			str = str + copy_var(&ntrp[x], str, env) + 1;
		else
		{
			ntrp[x] = str[0];
			++str;
		}
		while (ntrp[x] != 0)
			++x;
	}
	*delta = *delta + ((char *)str - (char *)d);
	return (ntrp);
}

t_list	*interparse(char *rl, t_list *env)
{
	t_list	*list;
	int		x;
	size_t	d;

	x = 0;
	d = 0;
	list = NULL;
	while (d < ft_strlen(rl))
	{
		while (rl[d] != 0 && ft_strchr(" \t\n", rl[d]))
			++d;
		if (rl[d] == 0)
			return (list);
		if (x == 0)
			list = memchk(ft_lstnew(interpret(&rl[d], &d, env)));
		if (x > 0)
			ft_lstadd_back(&list, memchk(\
				ft_lstnew(interpret(&rl[d], &d, env))));
		++x;
	}
	return (list);
}
