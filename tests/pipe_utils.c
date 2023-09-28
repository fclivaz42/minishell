/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:02:21 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/26 23:02:28 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_pdata pipex)
{
	int	x;

	x = 0;
	while (pipex.commands[x] != NULL)
		x++;
	return (x - 1);
}

int	**create_pipes(t_pdata pipex)
{
	int	x;
	int	**fd;

	x = -1;
	fd = (int **)ft_calloc(pipex.pipes + 1, sizeof(int));
	while (++ x != pipex.pipes)
		fd[x] = (int *)ft_calloc(2 + 1, sizeof(int));
	x = 0;
	while (x != pipex.pipes)
	{
		if (pipe(fd[x]) == -1)
			error_system(errno, "pipefail");
		x++;
	}
	return (fd);
}

void	close_pipes(t_pdata pipex)
{
	int	x;

	x = 0;
	close(pipex.infd);
	close(pipex.outfd);
	while (x != pipex.pipes)
	{
		close(pipex.fd[x][0]);
		close(pipex.fd[x][1]);
		x++;
	}
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
