/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:21:02 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/14 22:42:18 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quicc_copy(char *dest, char *src)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (dest[x] != 0)
		++x;
	while (src[++y] != 0)
		dest[x + y] = src[y];
}

char	**token_to_array(t_list *list)
{
	int		x;
	char	**commands;
	t_list	*args;

	args = list;
	x = ft_lstsize(list);
	commands = (char **)memchk(ft_calloc(x + 1, sizeof(char *)));
	x = 0;
	while (args != NULL)
	{
		commands[x] = (char *)args->content;
		args = args->next;
		++x;
	}
	return (commands);
}

char	**env_to_array(t_list *env)
{
	char	**ret;
	char	**tmp;
	t_list	*cpy;
	int		x;

	x = -1;
	cpy = env;
	ret = (char **)memchk(ft_calloc(ft_lstsize(cpy) + 1, sizeof(char *)));
	while (cpy != NULL)
	{
		tmp = (char **)cpy->content;
		ret[++x] = (char *)memchk(ft_calloc(ft_strlen(tmp[0]) + \
			ft_strlen(tmp[1]) + 2, sizeof(char)));
		quicc_copy(ret[x], tmp[0]);
		quicc_copy(ret[x], "=");
		quicc_copy(ret[x], tmp[1]);
		cpy = cpy->next;
	}
	return (ret);
}
