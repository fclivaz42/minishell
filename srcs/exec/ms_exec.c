/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:58:17 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/17 19:03:09 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	pipemoment(t_token *tkn)
{
	if (tkn->fd_in != STDIN_FILENO)
	{
		dup2(tkn->fd_in, STDIN_FILENO);
		close(tkn->fd_in);
	}
	if (tkn->fd_out != STDOUT_FILENO)
	{
		dup2(tkn->fd_out, STDOUT_FILENO);
		close(tkn->fd_out);
	}
}

static void	external(t_token *tkn, t_minishell *msdata)
{
	char	**commands;
	char	**env;
	int		ecode;

	tkn->pid = fork();
	if (tkn->pid < 0)
		memchk(NULL);
	if (tkn->pid == 0)
	{
		pipemoment(tkn);
		tkn->words->content = make_pathed(tkn->words->content, msdata->env);
		commands = token_to_array(tkn->words);
		env = env_to_array(msdata->env);
		if (execve(commands[0], commands, env) == -1)
		{
			msdata->ecode = error_system(-1, tkn->words->content);
			freexit(msdata);
		}
	}
}

static void	forked_exec(t_token *tkn, t_minishell *msdata)
{
	char	*cmd;

	cmd = tkn->words->content;
	tkn->pid = 0;
	if (!(ft_strncmp("echo", cmd, ft_strlen(cmd) + 1)))
		msdata->ecode = echo(tkn);
	else if (!(ft_strncmp("cd", cmd, ft_strlen(cmd) + 1)))
		msdata->ecode = cd(tkn, msdata);
	else if (!(ft_strncmp("export", cmd, ft_strlen(cmd) + 1)))
		msdata->ecode = mexport(tkn, msdata);
	else if (!(ft_strncmp("unset", cmd, ft_strlen(cmd) + 1)))
		msdata->ecode = unset(tkn, msdata);
	else if (!(ft_strncmp("env", cmd, ft_strlen(cmd) + 1)))
		msdata->ecode = env(tkn, msdata);
	else if (!(ft_strncmp("pwd", cmd, ft_strlen(cmd) + 1)))
	{
		ft_putendl_fd(msdata->pwd, tkn->fd_out);
		msdata->ecode = 0;
	}
	else if (!(ft_strncmp("exit", cmd, ft_strlen(cmd) + 1)))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		freexit(msdata);
	}
	else
		external(tkn, msdata);
}

void	execute(t_token *tkn, t_minishell *msdata)
{
	t_token	*etkn;
	char	*cmd;

	etkn = tkn;
	while (etkn != NULL)
	{
		cmd = etkn->words->content;
		printf("Executing command %s\n", cmd);
		forked_exec(etkn, msdata);
		if (tkn->fd_in != STDIN_FILENO)
			close(tkn->fd_in);
		if (tkn->fd_out != STDOUT_FILENO)
			close(tkn->fd_out);
		etkn = etkn->next;
	}
	etkn = tkn;
	while (etkn != NULL)
	{
		if (etkn->pid > 0)
			waitpid(etkn->pid, &msdata->ecode, 0);
		etkn = etkn->next;
	}
}

int	chredir(t_token *tkn, int mode)
{
	char	*test[2];

	if (mode == 0)
	{
		if (tkn->next != NULL && tkn->prev != NULL)
		{
			test[0] = tkn->next->words->content;
			test[1] = tkn->prev->words->content;
		}
		if (tkn->next == NULL || tkn->prev == NULL || \
			rsigncheck(test[0]) || rsigncheck(test[1]))
			return (1);
	}
	else
	{
		if (tkn->next != NULL && tkn->next->words->next != NULL)
		{
			test[0] = tkn->next->words->content;
			test[1] = tkn->next->words->next->content;
		}
		if (tkn->next == NULL || tkn->next->words->next == NULL || \
			rsigncheck(test[0]) || rsigncheck(test[1]))
			return (1);
	}
	return (0);
}
