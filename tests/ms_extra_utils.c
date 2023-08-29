/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:21:02 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/29 15:21:10 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	zerofree(char *s)
{
	ft_bzero(s, ft_strlen(s));
	free(s);
}

void	arrayfree(char **arr)
{
	int		x;

	x = -1;
	while (arr[++x] != NULL)
		zerofree(arr[x]);
	free(arr);
}

void	execute(char **commands, char *env[])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_system(errno, "syscall");
	if (pid == 0)
		if (execve(commands[0], commands, env) == -1)
			error_system(errno, "syscall");
}
