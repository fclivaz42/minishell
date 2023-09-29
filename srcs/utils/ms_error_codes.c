/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_codes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:47:53 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/29 23:04:08 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*memchk(void *str)
{
	if (str == NULL)
		return (error_system(errno, "MEMFAIL"));
	return (str);
}

void	*error_bad_format(char *src)
{
	ft_putstr_fd("\033[1;31mError:\033[0m \033[1;33m", STDERR_FILENO);
	ft_putstr_fd(src, 2);
	ft_putendl_fd("\033[0m: incorrect syntax.\n", STDERR_FILENO);
	return (NULL);
}

void	*error_system(int mode, char *file)
{
	if (mode == 2)
		perror(file);
	else if (mode == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
	{
		perror("\033[1;31mError\033[0m");
		exit(mode);
	}
	return (NULL);
}

void	*error_unsupported_character(char c)
{
	ft_putstr_fd("\033[1;31mError:\033[0m \033[1;33m", STDERR_FILENO);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\033[0m is an unsupported character.", STDERR_FILENO);
	return (NULL);
}
