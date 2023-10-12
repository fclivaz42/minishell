/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:31:44 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/12 20:20:52 by fclivaz          ###    LAUSANNE.CH      */
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

void	free_token(t_token *tkn)
{
	t_list	*env;
	t_list	*del;

	env = tkn->words;
	while (env != NULL)
	{
		del = env;
		zerofree(env->content);
		env = del->next;
		free(del);
	}
	free(tkn);
}

void	freexit(t_minishell *msdata)
{
	t_list	*env;
	t_list	*del;

	env = msdata->env;
	while (env != NULL)
	{
		del = env;
		arrayfree(env->content);
		env = del->next;
		free(del);
	}
	zerofree(msdata->pwd);
	free_token(msdata->commands);
	free(msdata);
	exit(0);
}
