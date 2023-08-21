/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:44:09 by fclivaz           #+#    #+#             */
/*   Updated: 2023/03/15 17:44:16 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*stop_space(char *rawprog)
{
	int		i;
	int		j;
	char	*prog;

	i = -1;
	j = -1;
	while (rawprog[++i] != 0)
	{
		if (rawprog[i] == ' ')
			break ;
	}
	prog = (char *)ft_calloc(i + 1, sizeof(char));
	check_failed_memory(prog);
	while (++j != i)
		prog[j] = rawprog[j];
	return (prog);
}

static char	**create_args(char *path, char *prog)
{
	int		id;
	char	*test;
	char	**args;

	id = -1;
	args = ft_split(path, ':');
	check_failed_memory(args);
	while (args[++id] != NULL)
	{
		if (args[id][ft_strlen(args[id]) - 1] != '/')
		{
			test = ft_strjoin(args[id], "/");
			check_failed_memory(test);
			free(args[id]);
			args[id] = test;
		}
		test = ft_strjoin(args[id], prog);
		check_failed_memory(test);
		free(args[id]);
		args[id] = test;
	}
	return (args);
}

static char	*find_path(char **env)
{
	int		id;
	char	*path;

	id = -1;
	while (env[++id] != NULL)
		if (!ft_strncmp(env[id], "PATH=", 5))
			path = ft_strchr(env[id], '/');
	return (path);
}

static char	*find_correct_path(char *rawprog, char **env)
{
	int		id;
	char	**args;
	char	*path;
	char	*prog;

	id = -1;
	prog = stop_space(rawprog);
	path = find_path(env);
	args = create_args(path, prog);
	id = -1;
	while (args[++id] != NULL)
	{
		if (open(args[id], O_RDONLY) != -1)
		{
			path = ft_strdup(args[id]);
			check_failed_memory(path);
			path[ft_strlen(path) - ft_strlen(prog)] = 0;
			free_array(args);
			free(prog);
			return (path);
		}
	}
	error_system(-1, prog);
	free(prog);
	exit(errno);
}

char	**check_arguments(char **arg, char **env)
{
	int		x;
	int		y;
	char	*path;
	char	**list;
	char	*thinginside;

	x = 2;
	while (arg[x] != NULL)
		x++;
	list = (char **)ft_calloc(x, sizeof(char **) - 1);
	check_failed_memory(list);
	y = -1;
	while (++y != x - 1)
	{
		if (arg[y + 3] == NULL)
			break ;
		path = find_correct_path(arg[y + 2], env);
		thinginside = ft_strjoin(path, arg[y + 2]);
		check_failed_memory(thinginside);
		free(path);
		list[y] = thinginside;
	}
	return (list);
}
