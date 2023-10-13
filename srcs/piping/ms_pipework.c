/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipework.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:31:38 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/13 04:27:13 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*rinoutfile(t_token **ptkn, int mode, int mode2)
{
	t_token	*ret;
	char	*path;
	t_token	*tkn;

	tkn = *ptkn;
	path = tkn->next->words->content;
	if (mode2 == 0)
		tkn->next->fd_in = open_infile(path);
	if (mode2 == 1)
		tkn->prev->fd_out = open_outfile(path, mode);
	tkn->prev->next = tkn->next;
	tkn->next->prev = tkn->prev;
	ret = tkn->next;
	free_token(tkn);
	return (ret);
}

static t_token	*rpipe(t_token **ptkn)
{
	t_token	*ret;
	t_token	*tkn;
	int		fd[2];

	tkn = *ptkn;
	pipe(fd);
	tkn->prev->fd_out = fd[1];
	tkn->next->fd_in = fd[0];
	tkn->prev->next = tkn->next;
	tkn->next->prev = tkn->prev;
	ret = tkn->next;
	free_token(tkn);
	return (ret);
}

static t_token	*rhd(t_token **ptkn)
{
	t_token	*ret;
	t_token	*tkn;
	char	*hd;

	tkn = *ptkn;
	hd = here_doc(tkn->next->words->content);
	zerofree(tkn->next->words->content);
	tkn->next->words->content = hd;
	ft_lstadd_back(&tkn->prev->words, tkn->next->words);
	tkn->prev->next = tkn->next->next;
	tkn->next->next->prev = tkn->prev;
	ret = tkn->next->next;
	free_token(tkn);
	return (ret);
}

static t_token	*rcompare(t_token **tkn)
{
	t_token	*pass;
	char	*str;

	pass = *tkn;
	str = pass->words->content;
	if (!ft_strncmp(str, "<<", 2))
		return (rhd(&pass));
	else if (!ft_strncmp(str, ">>", 2))
		return (rinoutfile(&pass, O_APPEND, 1));
	else if (!ft_strncmp(str, "|", 1))
		return (rpipe(&pass));
	else if (!ft_strncmp(str, "<", 1))
		return (rinoutfile(&pass, 0, 0));
	else if (!ft_strncmp(str, ">", 1))
		return (rinoutfile(&pass, O_TRUNC, 1));
	else
	{
		printf("token %p is NOT a redir\n", pass);
		return (pass->next);
	}
}

t_token	*pipework(t_token *tkn)
{
	t_token	*tkntest;

	tkntest = tkn;
	tknprint(tkntest);
	while (tkntest != NULL)
		tkntest = rcompare(&tkntest);
	ft_putendl_fd("", 1);
	ft_putendl_fd("--------", 1);
	ft_putendl_fd("", 1);
	return (tkn);
}
