/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:31:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/29 05:57:49 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fixup_env(t_minishell *msdata)
{
	char	**split;
	char	*shell;
	int		x;

	x = -1;
		new_env_var(msdata, "SHLVL", "1");
	shell = (char *)memchk(ft_calloc(ft_strlen(find_env(msdata->env, "_")), \
		sizeof(char)));
	split = memchk(ft_split(find_env(msdata->env, "_"), '/'));
	while (split[++x] != 0)
	{
		if (ft_strncmp(split[x], ".", 1))
		{
			quicc_copy(shell, "/");
			quicc_copy(shell, split[x]);
		}
	}
	arrayfree(split);
	if (find_env(msdata->env, "SHELL"))
		delete_env(msdata, "SHELL");
	new_env_var(msdata, "SHELL", shell);
	free(shell);
	if (find_env(msdata->env, "_"))
		delete_env(msdata, "_");
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
		if (find_env(msdata->env, "SHLVL") != NULL)
		{
			value = memchk(ft_itoa(ft_atoi(find_env(msdata->env, "SHLVL")) + 1));
			replace_env(msdata->env, "SHLVL", value);
			zerofree(value);
		}
		else
			new_env_var(msdata, "SHLVL", "1");
		fixup_env(msdata);
	}
}
