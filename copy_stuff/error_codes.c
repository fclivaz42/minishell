/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:03:40 by fclivaz           #+#    #+#             */
/*   Updated: 2023/03/15 17:03:49 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_failed_memory(void *str)
{
	if (str == NULL)
		error_system(errno, "MEMFAIL");
}

void	error_incorrect_use(void)
{
	ft_printf("\033[1;31mUsage:\033[0m pipex infile cmd1 cmd2 outfile\n");
	exit (2);
}

void	error_bad_format(char *src)
{
	ft_printf("\033[1;31mError:\033[0m ");
	ft_printf("\033[1;33m%s\033[0m incorrect syntax.\n", src);
	exit (2);
}

void	error_system(int mode, char *file)
{
	if (mode == 2)
		perror(file);
	else if (mode == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(errno);
	}
	else
		perror("\033[1;31mError\033[0m");
	exit(mode);
}
