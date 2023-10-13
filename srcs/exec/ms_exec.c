/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:58:17 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/13 19:23:13 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	external(t_token *tkn, t_minishell *msdata)
{
	char	**commands;

	tkn->words->content = make_pathed(tkn->words->content, msdata->env);
	commands = token_to_array(tkn->words);
	if (execve(commands[0], commands, env_to_array(msdata->env)) == -1)
		exit (error_system(-1, tkn->words->content));
	return (0);
}

static int	forked_exec(t_token *tkn, t_minishell *msdata)
{
	char	*cmd;

	cmd = tkn->words->content;
	if (!(ft_strncmp("echo", cmd, ft_strlen(cmd) + 1)))
		exit (echo(tkn));
	else if (!(ft_strncmp("cd", cmd, ft_strlen(cmd) + 1)))
		exit (cd(tkn, msdata));
	else if (!(ft_strncmp("export", cmd, ft_strlen(cmd) + 1)))
		exit (mexport(tkn, msdata));
	else if (!(ft_strncmp("unset", cmd, ft_strlen(cmd) + 1)))
		exit (unset(tkn, msdata));
	else if (!(ft_strncmp("env", cmd, ft_strlen(cmd) + 1)))
		exit (env(tkn, msdata));
	else if (!(ft_strncmp("pwd", cmd, ft_strlen(cmd) + 1)))
		ft_putendl_fd(msdata->pwd, STDOUT_FILENO);
	else if (!(ft_strncmp("exit", cmd, ft_strlen(cmd) + 1)))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		freexit(msdata);
	}
	else
		return (external(tkn, msdata));
	return (0);
}

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

int	execute(t_token *tkn, t_minishell *msdata)
{
	t_token	*etkn;

	etkn = tkn;
	while (etkn != NULL)
	{
		printf("Executing command %s\n", etkn->words->content);
		msdata->pid = fork();
		if (msdata->pid < 0)
			memchk(NULL);
		if (msdata->pid == 0)
		{
			pipemoment(etkn);
			return (forked_exec(etkn, msdata));
		}
		etkn = etkn->next;
	}
	waitpid(msdata->pid, &msdata->ecode, 0);
	return (0);
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
			ft_strchr("<|>", test[0][1]) || ft_strchr("<|>", test[1][1]))
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
			ft_strchr("<|>", test[0][1]) || ft_strchr("<|>", test[1][1]))
			return (1);
	}
	return (0);
}
