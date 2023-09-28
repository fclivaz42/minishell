/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:21:02 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/28 22:52:02 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	zerofree(char *s)
{
	ft_bzero(s, ft_strlen(s));
	free(s);
}

void	arrayfree(char **arr)
{
	int		x;

	x = -1;
	while (arr[++x] != NULL)
		zerofree(arr[x]);
	free(arr);
}

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

char	**concatenate(t_list *list)
{
	int		x;
	char	**commands;
	t_list	*args;
	t_list	*lstfree;

	args = list;
	x = ft_lstsize(list);
	commands = (char **)memchk(ft_calloc(x + 1, sizeof(char *)));
	x = 0;
	while (args != NULL)
	{
		if (x > 0)
			free(lstfree);
		commands[x] = (char *)args->content;
		lstfree = args;
		args = args->next;
		++x;
	}
	if (x > 0)
		free(lstfree);
	return (commands);
}

char	**list_to_char(t_list *env)
{
	char	**ret;
	char	**tmp;
	char	*var;
	int		x;

	x = -1;
	ret = (char **)memchk(ft_calloc(ft_lstsize(env) + 1, sizeof(char *)));
	while (env != NULL)
	{
		tmp = (char **)env->content;
		var = (char *)memchk(ft_calloc(ft_strlen(tmp[0]) + \
			ft_strlen(tmp[1]) + 2, sizeof(char)));
		quicc_copy(var, tmp[0]);
		quicc_copy(var, "=");
		quicc_copy(var, tmp[1]);
		ret[++x] = var;
		env = env->next;
	}
	return (ret);
}
