/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:58:17 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/16 17:59:14 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(char **commands, t_list	*env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_system(errno, "syscall");
	if (pid == 0)
		if (execve(commands[0], commands, list_to_char(env)) == -1)
			error_system(errno, "syscall");
}
