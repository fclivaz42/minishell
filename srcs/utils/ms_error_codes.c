/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_codes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:47:53 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/26 19:53:13 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_failed_memory(void *str)
{
	if (str == NULL)
		error_system(errno, "MEMFAIL");
}

void	*error_bad_format(char *src)
{
	ft_printf("\033[1;31mError:\033[0m ");
	ft_printf("\033[1;33m%s\033[0m incorrect syntax.\n", src);
	return (NULL);
}

void	error_system(int mode, char *file)
{
	if (mode == 2)
		perror(file);
	else if (mode == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror("\033[1;31mError\033[0m");
	exit(mode);
}

void	*error_unsupported_character(char c)
{
	ft_printf("\033[1;31mError:\033[0m ");
	ft_printf("\033[1;33m%c\033[0m unsupported character.\n", c);
	return (NULL);
}
