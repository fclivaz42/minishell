/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_codes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:47:53 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/21 18:48:03 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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