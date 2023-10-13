/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:31:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/13 16:12:27 by fclivaz          ###    LAUSANNE.CH      */
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
}

static void	fix_shell(t_minishell *msdata, char *av)
{
	char	*shell;

	shell = relative_dir(memchk(ft_split(av, '/')), msdata->pwd);
	if (find_env(msdata->env, "SHELL"))
		replace_env(msdata->env, "SHELL", shell);
	else
		new_env_var(msdata, "SHELL", shell);
	zerofree(shell);
}

static void	copy_env(char *env[], t_minishell *msdata)
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

void	init_mshell(char *av, char *env[], t_minishell *msdata)
{
	copy_env(env, msdata);
	if (find_env(msdata->env, "PWD"))
		msdata->pwd = memchk(ft_strdup(find_env(msdata->env, "PWD")));
	else
		msdata->pwd = memchk(getcwd(NULL, 0));
	fix_shell(msdata, av);
	printf("\nWelcome to %sminishell%s beta %sv0.9%s!\n\n", CBBL, RSET, \
		ERED, RSET);
}
