/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipework.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:31:38 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/17 21:20:10 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* --- CHREDIR IS IN MS_EXEC --- */

static t_token	*rinfile(t_minishell *msdata, t_token *tkn, int *v)
{
	t_token	*ret;
	t_list	*del;

	if (chredir(tkn, 1))
		return (error_bad_piping(tkn->words->content, v, 1));
	tkn->next->fd_in = open_file(msdata, tkn->next->words->content, -1, v);
	if (tkn->next->fd_in == -1)
		return (NULL);
	if (tkn->prev != NULL)
		tkn->prev->next = tkn->next;
	tkn->next->prev = tkn->prev;
	del = tkn->next->words;
	tkn->next->words = del->next;
	zerofree(del->content);
	free(del);
	ret = tkn->next;
	free_token(tkn);
	msdata->commands = ret;
	return (ret);
}

static t_token	*routfile(t_minishell *msdata, t_token *tkn, int md, int *v)
{
	char	*path;

	if (chredir(tkn, 0))
		return (error_bad_piping(tkn->words->content, v, 1));
	path = tkn->next->words->content;
	tkn->prev->fd_out = open_file(msdata, path, md, v);
	if (tkn->prev->fd_out == -1)
		return (NULL);
	if (tkn->next->next != NULL)
		error_bad_piping(tkn->next->words->content, v, 0);
	tkn->prev->next = NULL;
	clear_tokens(tkn);
	return (NULL);
}

static t_token	*rpipe(t_token *tkn, int *v)
{
	t_token	*ret;
	int		fd[2];

	if (chredir(tkn, 0))
		return (error_bad_piping(tkn->words->content, v, 1));
	pipe(fd);
	tkn->prev->fd_out = fd[1];
	tkn->next->fd_in = fd[0];
	tkn->prev->next = tkn->next;
	tkn->next->prev = tkn->prev;
	ret = tkn->next;
	free_token(tkn);
	return (ret);
}

static t_token	*rhd(t_token *tkn, int *v)
{
	t_token	*ret;
	char	*hd;
	int		fd[2];

	if (chredir(tkn, 0))
		return (error_bad_piping(tkn->words->content, v, 1));
	pipe(fd);
	hd = here_doc(tkn->next->words->content);
	ft_putstr_fd(hd, fd[1]);
	tkn->prev->fd_in = fd[0];
	zerofree(tkn->next->words->content);
	zerofree(hd);
	tkn->prev->next = tkn->next->next;
	if (tkn->next->next != NULL)
		tkn->next->next->prev = tkn->prev;
	else
		tkn->next->next = NULL;
	ret = tkn->next->next;
	free_token(tkn);
	return (ret);
}

t_token	*rcmp(t_minishell *msdata, t_token *tkn, int *valid)
{
	char	*str;

	str = tkn->words->content;
	if (!ft_strncmp(str, "<<", 2))
		return (rhd(tkn, valid));
	else if (!ft_strncmp(str, ">>", 2))
		return (routfile(msdata, tkn, O_APPEND, valid));
	else if (!ft_strncmp(str, "|", 1))
		return (rpipe(tkn, valid));
	else if (!ft_strncmp(str, "<", 1))
		return (rinfile(msdata, tkn, valid));
	else if (!ft_strncmp(str, ">", 1))
		return (routfile(msdata, tkn, O_TRUNC, valid));
	else
		return (tkn->next);
}
