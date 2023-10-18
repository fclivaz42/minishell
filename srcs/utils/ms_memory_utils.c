/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:31:44 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 21:38:25 by fclivaz          ###    LAUSANNE.CH      */
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

void	clear_tokens(t_token *tkn)
{
	t_token	*mem;
	t_token	*del;

	mem = tkn;
	while (mem != NULL)
	{
		del = mem;
		mem = mem->next;
		free_token(del);
	}
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
	int		ecode;

	env = msdata->env;
	while (env != NULL)
	{
		del = env;
		arrayfree(env->content);
		env = del->next;
		free(del);
	}
	zerofree(msdata->pwd);
	clear_tokens(msdata->commands);
	ecode = msdata->ecode;
	free(msdata);
	exit(ecode);
}
