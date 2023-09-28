/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/28 22:48:43 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_list	*append_argument(char *str)
{
	char	*argument;
	char	c;
	int		len;

	c = str[0];
	len = 0;
	if (c == 34 || c == 39)
	{
		++str;
		while (!(str[len] == 34 || str[len] == 39 || str[len] == 0))
			++len;
	}
	else
		while (!(str[len] == ' ' || str[len] == 0))
			++len;
	argument = (char *)memchk(ft_calloc(len + 1, sizeof(char)));
	ft_strlcpy(argument, str, len + 1);
	return (memchk(ft_lstnew(argument)));
}

char	*make_token(char *str)
{
	int		x;
	int		y;
	char	*token;

	x = -1;
	while (!(ft_strchr(" \t\n\0", str[++x])))
	{
		if (ft_strchr("{}[]()\\;%~`?!#", str[x]))
			return(error_unsupported_character(str[x]));
	}
}

t_list	*ms_fullparse(char *str, t_list *env)
{
	t_list	*list;
	t_list	*next;

	if (ft_strlen(str) == 0)
		return (NULL);
	while (ft_strchr(" \t\n\0", *str))
		++str;
	if (*str != 0)
		return (NULL);
	list = memchk(ft_lstnew(make_token(str)));
	str = str + ft_strlen(list->content);
	while (*str != 0)
	{
		while (ft_strchr(" \t\n\0", *str))
			++str;
		if (*str != 0)
		{
			next = memchk(ft_lstnew(make_token(str)));
			ft_lstadd_back(&list, next);
			str = str + ft_strlen(next->content);
		}
	}
	return (list);
}
