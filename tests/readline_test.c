/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:33:31 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/09 22:33:38 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_realloc(char *str, char *str2, int psize)
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

char	*here_doc_a_la_con(char *eof)
{
	char	*str1;
	char	*strfull;

	strfull = NULL;
	while (1)
	{
		str1 = readline("∙ ");
		if (!ft_strncmp(str1, eof, ft_strlen(eof) + 1))
		{
			zerofree(str1);
			break ;
		}
		if (strfull == NULL)
			strfull = memchk(ft_strdup(str1));
		else
			strfull = read_realloc(strfull, str1, ft_strlen(str1));
		free(str1);
	}
	return (strfull);
}

int	main(void)
{
	char	*cmd1;
	char	*hd;

	while (1)
	{
		cmd1 = readline("balls>");
		if (!ft_strncmp(cmd1, "<<", 2))
		{
			hd = here_doc_a_la_con(&cmd1[3]);
			puts(hd);
			zerofree(hd);
		}
		else if (!ft_strncmp(cmd1, "exit", 5))
		{
			zerofree(cmd1);
			exit (0);
		}
		else
			puts(cmd1);
		zerofree(cmd1);
	}
	return (0);
}
