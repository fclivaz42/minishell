/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipework.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:31:38 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/13 03:38:26 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	rinoutfile(t_token *tkn, int mode, int mode2)
{
	char	*path;

	path = tkn->next->words->content;
	if (mode2 == 0)
		tkn->next->fd_in = open_infile(path);
	if (mode2 == 1)
		tkn->prev->fd_out = open_outfile(path, mode);
	tkn->prev->next = tkn->next;
	tkn->next->prev = tkn->prev;
	free_token(tkn);
}

static void	rpipe(t_token *tkn)
{
	int	fd[2];

	pipe(fd);
	tkn->prev->fd_out = fd[1];
	tkn->next->fd_in = fd[0];
	tkn->prev->next = tkn->next;
	tkn->next->prev = tkn->prev;
	free_token(tkn);
}

static void	rhd(t_token *tkn)
{
	int		fd[2];
	char	*hd;

	hd = here_doc(tkn->next->words->content);
	zerofree(tkn->next->words->content);
	tkn->next->words->content = hd;
	ft_lstadd_back(&tkn->prev->words, tkn->next->words);
	tkn->prev->next = tkn->next->next;
	tkn->next->next->prev = tkn->prev;
	free_token(tkn);
}

static void	rcompare(t_token *tkn)
{
	char	*str;

	str = tkn->words->content;
	if (!ft_strncmp(str, "<<", 2))
		rhd(tkn);
	else if (!ft_strncmp(str, ">>", 2))
		rinoutfile(tkn, O_APPEND, 1);
	else if (!ft_strncmp(str, "|", 1))
		rpipe(tkn);
	else if (!ft_strncmp(str, "<", 1))
		rinoutfile(tkn, 0, 0);
	else if (!ft_strncmp(str, ">", 1))
		rinoutfile(tkn, O_TRUNC, 1);
	else
		return ;
}

t_token	*pipework(t_token *tkn)
{
	t_token	*tkntest;

	tkntest = tkn;
	while (tkntest != NULL)
	{
		tknprint(tkntest);
		rcompare(tkntest);
		tknprint(tkntest);
		tkntest = tkntest->next;
	}
	return (tkn);
}
