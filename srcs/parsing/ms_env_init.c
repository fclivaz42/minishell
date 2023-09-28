/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:31:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/28 22:49:29 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fixup_env(t_list *env)
{
	char	**split;
	char	*shell;
	int		x;

	x = -1;
	if (find_env(env, "SHLVL") != NULL)
		replace_env(env, "SHLVL", ft_itoa(ft_atoi(find_env(env, "SHLVL")) + 1));
	else
		new_env_var(env, "SHLVL", "1");
	shell = (char *)memchk(ft_calloc(ft_strlen(getenv("_")), sizeof(char)));
	split = memchk(ft_split(getenv("_"), '/'));
	while (split[++x] != 0)
	{
		if (ft_strncmp(split[x], ".", 1))
		{
			quicc_copy(shell, "/");
			quicc_copy(shell, split[x]);
		}
	}
	arrayfree(split);
	if (find_env(env, "SHELL"))
		delete_env(env, "SHELL");
	new_env_var(env, "SHELL", shell);
	free(shell);
	delete_env(env, "_");
}

t_list	*copy_env(char *env[])
{
	int		x;
	int		len;
	char	**var;
	t_list	*newenv;

	x = -1;
	while (env[++x] != NULL)
	{
		var = (char **)memchk(ft_calloc(3, sizeof(char *)));
		len = ft_strlen(env[x]) - ft_strlen(ft_strchr(env[x], '='));
		var[0] = (char *)memchk(ft_calloc(len + 1, sizeof(char)));
		ft_strlcpy(var[0], env[x], len + 1);
		var[1] = memchk(ft_strdup(ft_strchr(env[x], '=') + 1));
		if (x == 0)
			newenv = ft_lstnew(var);
		if (x > 0)
			ft_lstadd_back(&newenv, memchk(ft_lstnew(var)));
	}
	if (env != NULL)
		fixup_env(newenv);
	if (__APPLE__ && !find_env(newenv, "HOSTNAME"))
		new_env_var(newenv, "HOSTNAME", "macOS");
	return (newenv);
}
