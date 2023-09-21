/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_part_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:17:11 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/21 21:35:50 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_token *tkn, t_minishell *msdata)
{
	char	**print;
	int		x;

	x = -1;
	if (msdata->env == NULL)
		return(write(tkn->fd_out, "\n", 1));
	print = list_to_char(msdata->env);
	while (print[++x] != NULL)
		ft_putendl_fd(print[x], tkn->fd_out);
	arrayfree(print);
	return (0);
}

int	unset(t_token *tkn, t_minishell *msdata)
{
	delete_env(msdata->env, tkn->words->next->content);
	return (0);
}

int	mexport(t_token *tkn, t_minishell *msdata)
{
	char	*var;
	char	*str;
	int		x;	

	str = ft_strchr(tkn->words->next->content, '=');
	if (str == NULL)
		return (1);
	x = -1;
	str++;

	return (0);
}
