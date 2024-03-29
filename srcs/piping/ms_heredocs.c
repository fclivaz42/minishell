/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:55:57 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 19:45:04 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_realloc(char *str, char *str2, int psize)
{
	char	*newstr;

	newstr = (char *)memchk(ft_calloc(ft_strlen(str) + psize + 2, \
		sizeof(char)));
	quicc_copy(newstr, str);
	newstr[ft_strlen(str)] = '\n';
	zerofree(str);
	if (str2 != NULL)
		quicc_copy(newstr, str2);
	return (newstr);
}

char	*here_doc(char *eof)
{
	char	*rl;
	char	*strfull;

	strfull = NULL;
	while (1)
	{
		rl = readline("∙ ");
		if (rl == NULL)
			return (strfull);
		if (!ft_strncmp(rl, eof, ft_strlen(eof) + 1))
		{
			zerofree(rl);
			break ;
		}
		if (strfull == NULL)
			strfull = memchk(ft_strdup(rl));
		else
			strfull = read_realloc(strfull, rl, ft_strlen(rl));
		free(rl);
	}
	return (strfull);
}

int	open_file(t_minishell *msdata, char *path, int crtr, int *v)
{
	int	fd;

	if (crtr >= 0)
		fd = open(path, O_WRONLY | crtr | O_CREAT, 0644);
	else
		fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		msdata->ecode = error_system(errno, path);
		*v = 1;
		clear_tokens(msdata->commands);
	}
	return (fd);
}

int	rsigncheck(char *str)
{
	if (!ft_strncmp(str, "<<", ft_strlen(str) + 1))
		return (1);
	else if (!ft_strncmp(str, ">>", ft_strlen(str) + 1))
		return (1);
	else if (!ft_strncmp(str, "|", ft_strlen(str) + 1))
		return (1);
	else if (!ft_strncmp(str, "<", ft_strlen(str) + 1))
		return (1);
	else if (!ft_strncmp(str, ">", ft_strlen(str) + 1))
		return (1);
	else
		return (0);
}

t_token	*pipework(t_minishell *msdata, t_token *tkn, int *valid)
{
	t_token	*tkntest;

	tkntest = tkn;
	while (tkntest != NULL)
	{
		tkntest = rcmp(msdata, tkntest, valid);
		if (*valid)
			break ;
	}
	if (msdata->commands != NULL)
		tkn = msdata->commands;
	return (tkn);
}
