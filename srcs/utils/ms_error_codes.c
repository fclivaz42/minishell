/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_codes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:47:53 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 17:34:05 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*memchk(void *str)
{
	if (str == NULL)
	{
		perror("\033[1;31mError\033[0m");
		exit(errno);
	}
	return (str);
}

int	error_bad_format(char *src, t_minishell *msdata)
{
	ft_putstr_fd("\033[1;31mError:\033[0m \033[1;33m", STDERR_FILENO);
	ft_putstr_fd(src, STDERR_FILENO);
	ft_putendl_fd("\033[0m: incorrect syntax.\n", STDERR_FILENO);
	msdata->ecode = 1;
	return (1);
}

int	error_system(int mode, char *file)
{
	if (mode == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
		perror(file);
	return (127);
}

int	error_unsupported_character(char c, t_minishell *msdata)
{
	ft_putstr_fd("\033[1;31mError:\033[0m \033[1;33m", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putendl_fd("\033[0m is an unsupported character.", STDERR_FILENO);
	msdata->ecode = 1;
	return (1);
}

void	*error_bad_piping(t_token *tkn, int *v, int mode)
{
	t_token	*clear;

	clear = tkn;
	if (mode)
	{
		ft_putstr_fd("\033[1;31mError:\033[0m bad parsing near \"\033[1;33m", \
			STDERR_FILENO);
		ft_putstr_fd(tkn->words->content, STDERR_FILENO);
		ft_putendl_fd("\033[0m\"", STDERR_FILENO);
		*v = 1;
		while (clear->prev != NULL)
			clear = clear->prev;
		clear_tokens(clear);
	}
	else
	{
		ft_putstr_fd("\033[1;33mWarning: ", STDERR_FILENO);
		ft_putstr_fd("\033[0mtrailing arguments found after '", STDERR_FILENO);
		ft_putstr_fd(tkn->next->words->content, STDERR_FILENO);
		ft_putendl_fd("'. Those will be ignored.", STDERR_FILENO);
	}
	return (NULL);
}
