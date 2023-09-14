/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:27:28 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/14 16:36:44 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*squigglify(t_list *env, char *pwd)
{
	char	*home;
	char	*squiggled;

	home = find_env(env, "HOME");
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (ft_strdup(pwd));
	pwd = pwd + ft_strlen(home);
	squiggled = (char *)ft_calloc(ft_strlen(pwd) + 2, sizeof(char));
	ft_strlcpy(squiggled, "~", 2);
	ft_strlcat(squiggled, pwd, ft_strlen(pwd) + 2);
	return (squiggled);
}

void	build_prompt(char *prompt, char **vars)
{
	quicc_copy(prompt, "[");
	quicc_copy(prompt, vars[0]);
	quicc_copy(prompt, "@");
	quicc_copy(prompt, vars[1]);
	quicc_copy(prompt, "]: ");
	quicc_copy(prompt, vars[2]);
	quicc_copy(prompt, ">$ ");
	zerofree(vars[2]);
}

char	*readline_proompter(t_list *env)
{
	char	*vars[3];
	char	*prompt;

	vars[0] = find_env(env, "USER");
	if (__APPLE__)
		vars[1] = "macOS";
	else
		vars[1] = find_env(env, HOSTNAME);
	vars[2] = squigglify(env, find_env(env, "PWD"));
	prompt = (char *)ft_calloc(ft_strlen(vars[0]) + \
		ft_strlen(vars[1]) + ft_strlen(vars[2]) + \
		ft_strlen("[@]:  >$ ") + 1, sizeof(char));
	build_prompt(prompt, vars);
	return (prompt);
}
