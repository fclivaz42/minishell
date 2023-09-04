/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:31:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/04 19:31:40 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fixup_env(t_list *env)
{
	char	*ms_path;
	char	*shell;
	int		x;

	if (find_env(env, "SHLVL") != NULL)
		replace_env(env, "SHLVL", ft_itoa(ft_atoi(find_env(env, "SHLVL")) + 1));
	else
		new_env_var(env, "SHLVL", "1");
	ms_path = find_env(env, "_");
	shell = (char *)ft_calloc(ft_strlen(ms_path), 1);
	x = 0;
	while (*ms_path != 0)
	{
		if (ms_path[0] == '/' && ms_path[1] == '.' && ms_path[2] == '/')
			ms_path = ms_path + 2;
		shell[x] = ms_path[0];
		++ms_path;
		++x;
	}
	replace_env(env, "SHELL", shell);
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
		var = (char **)ft_calloc(3, sizeof(char *));
		check_failed_memory(var);
		len = ft_strlen(env[x]) - ft_strlen(ft_strchr(env[x], '='));
		var[0] = (char *)ft_calloc(len + 1, sizeof(char));
		check_failed_memory(var[0]);
		ft_strlcpy(var[0], env[x], len + 1);
		var[1] = ft_strdup(ft_strchr(env[x], '=') + 1);
		check_failed_memory(var[1]);
		if (x == 0)
			newenv = ft_lstnew(var);
		if (x > 0)
			ft_lstadd_back(&newenv, ft_lstnew(var));
	}
	fixup_env(newenv);
	return (newenv);
}
