/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:58:17 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/29 21:26:44 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	external(t_token *tkn, t_list *env)
{
	int		pid;
	char	**commands;

	pid = fork();
	if (pid < 0)
		error_system(errno, "syscall");
	if (pid == 0)
	{
		commands = concatenate(tkn->words);
		// --- PIPE MOMENT
		if (execve(commands[0], commands, list_to_char(env)) == -1)
			error_system(errno, "syscall");
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
		external(tkn, msdata->env);
	return (0);
}
