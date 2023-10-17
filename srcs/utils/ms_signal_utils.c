/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:45:37 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/17 21:21:55 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	waitstatus(t_token *tkn, t_minishell *msdata)
{
	t_token	*etkn;
	int		excode;

	etkn = tkn;
	excode = 0;
	while (etkn != NULL)
	{
		if (etkn->pid > 0)
		{
			waitpid(etkn->pid, &excode, 0);
			if (WIFSIGNALED(excode))
				msdata->ecode = 128 + WTERMSIG(excode);
			if (WIFEXITED(excode))
				msdata->ecode = WEXITSTATUS(excode);
		}
		etkn = etkn->next;
	}
}
