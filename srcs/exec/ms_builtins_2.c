/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:17:11 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/16 20:38:37 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_token *tkn, t_minishell *msdata)
{
	char	**print;
	int		x;

	x = -1;
	if (msdata->env == NULL)
		return (write(tkn->fd_out, "\n", 1));
	print = env_to_array(msdata->env);
	while (print[++x] != NULL)
		ft_putendl_fd(print[x], tkn->fd_out);
	arrayfree(print);
	return (0);
}

int	unset(t_token *tkn, t_minishell *msdata)
{
	t_list	*test;

	if (tkn->words->next == NULL)
		return (!error_bad_format("unset", msdata));
	test = tkn->words->next;
	while (test != NULL)
	{
		delete_env(msdata, test->content);
		test = test->next;
	}
	return (0);
}

int	mexport(t_token *tkn, t_minishell *msdata)
{
	char	*var;
	char	*str;
	int		size;

	if (tkn->words->next == NULL)
		return (env(tkn, msdata));
	str = ft_strchr(tkn->words->next->content, '=');
	if (str == NULL)
	{
		error_bad_format(tkn->words->next->content, msdata);
		return (1);
	}
	str++;
	size = (char *)str - (char *)tkn->words->next->content;
	var = (char *)memchk(ft_calloc(size, sizeof(char)));
	ft_strlcpy(var, tkn->words->next->content, size);
	if (find_env(msdata->env, var) != NULL)
		replace_env(msdata->env, var, str);
	else
		new_env_var(msdata, var, str);
	zerofree(var);
	return (0);
}
