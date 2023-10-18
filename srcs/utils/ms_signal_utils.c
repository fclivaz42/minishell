/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:37 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 20:19:10 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	waitstatus(t_token *tkn, t_minishell *msdata)
{
	t_token	*etkn;
	int		excode;

	if (msdata->forked == 0)
		return ;
	etkn = tkn;
	excode = 0;
	while (etkn != NULL)
	{
		waitpid(etkn->pid, &excode, 0);
		if (WIFSIGNALED(excode))
			msdata->ecode = 128 + WTERMSIG(excode);
		if (WIFEXITED(excode))
			msdata->ecode = WEXITSTATUS(excode);
		etkn = etkn->next;
	}
}

static void	schild(int k)
{
	(void)k;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
}

void	sigtochild(void)
{
	signal(SIGINT, schild);
	signal(SIGQUIT, schild);
}

void	interrupt(int k)
{
	(void)k;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	sigskip(int k)
{
	(void)k;
}
