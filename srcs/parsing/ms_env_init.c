/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:31:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/30 00:36:12 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fix_shlvl(t_minishell *msdata)
{
	char	*value;

	if (find_env(msdata->env, "SHLVL") != NULL)
	{
		value = memchk(ft_itoa(ft_atoi(find_env(msdata->env, "SHLVL")) + 1));
		replace_env(msdata->env, "SHLVL", value);
		zerofree(value);
	}
	else
		new_env_var(msdata, "SHLVL", "1");
	if (find_env(msdata->env, "SHELL"))
		replace_env(msdata->env, "SHELL", "minishell");
	else
		new_env_var(msdata, "SHELL", "minishell");
}

void	copy_env(char *env[], t_minishell *msdata)
{
	int		x;
	char	*newvar;
	char	*value;

	x = -1;
	msdata->env = NULL;
	while (env[++x] != NULL)
	{
		value = ft_strchr(env[x], '=');
		value[0] = 0;
		++value;
		newvar = env[x];
		new_env_var(msdata, newvar, value);
	}
	if (__APPLE__ && !find_env(msdata->env, "HOSTNAME"))
		new_env_var(msdata, "HOSTNAME", "macOS");
	if (env != NULL)
	{
		fix_shlvl(msdata);
		if (find_env(msdata->env, "_"))
			delete_env(msdata, "_");
	}
}
