/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:55:57 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/13 00:31:53 by fclivaz          ###    LAUSANNE.CH      */
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

int	open_outfile(char *path, int mode)
{
	int	fd;

	fd = open(path, O_WRONLY | mode | O_CREAT, 0644);
	if (fd < 0)
		error_system(errno, path);
	return (fd);
}

int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_system(errno, path);
	return (fd);
}
