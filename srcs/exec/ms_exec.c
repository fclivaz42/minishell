/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:58:17 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/30 23:32:00 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	external(t_token *tkn, t_minishell *msdata)
{
	char	**commands;

	msdata->pid = fork();
	if (msdata->pid < 0)
		error_system(errno, "syscall");
	if (msdata->pid == 0)
	{
		tkn->words->content = make_pathed(tkn->words->content, msdata->env);
		commands = token_to_array(tkn->words);
		// --- PIPE MOMENT
		if (execve(commands[0], commands, env_to_array(msdata->env)) == -1)
			error_system(errno, tkn->words->content);
	}
}

int	execute(t_token *tkn, t_minishell *msdata)
{
	char	*cmd;

	cmd = tkn->words->content;
	if (!(ft_strncmp("echo", cmd, ft_strlen(cmd) + 1)))
		return (echo(tkn));
	else if (!(ft_strncmp("cd", cmd, ft_strlen(cmd) + 1)))
		return (cd(tkn, msdata));
	else if (!(ft_strncmp("export", cmd, ft_strlen(cmd) + 1)))
		return (mexport(tkn, msdata));
	else if (!(ft_strncmp("unset", cmd, ft_strlen(cmd) + 1)))
		return (unset(tkn, msdata));
	else if (!(ft_strncmp("env", cmd, ft_strlen(cmd) + 1)))
		return (env(tkn, msdata));
	else if (!(ft_strncmp("pwd", cmd, ft_strlen(cmd) + 1)))
		ft_putendl_fd(msdata->pwd, tkn->fd_out);
	else if (!(ft_strncmp("exit", cmd, ft_strlen(cmd) + 1)))
	{
		ft_putendl_fd("exit", 1);
		freexit(msdata);
	}
	else
		external(tkn, msdata);
	return (0);
}
