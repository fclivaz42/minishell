/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/14 18:30:15 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**unpack_path(t_list *env)
{
	int		id;
	char	*path;
	char	**pathvars;

	id = -1;
	path = find_env(env, "PATH");
	if (path == NULL)
		return (NULL);
	pathvars = ft_split(path, ':');
	check_failed_memory(pathvars);
	while (pathvars[++id] != NULL)
		if (pathvars[id][ft_strlen(pathvars[id])] == '/')
			pathvars[id][ft_strlen(pathvars[id])] = 0;
	return (pathvars);
}

static char	*find_real_cmd(char *cmd, int cmdlen, char **p)
{
	int		x;
	int		fd;
	char	*fcmd;

	x = -1;
	while (p[++x] != NULL)
	{
		fcmd = (char *)ft_calloc(cmdlen + ft_strlen(p[x]) + 1, sizeof(char));
		check_failed_memory(fcmd);
		ft_strlcpy(fcmd, p[x], ft_strlen(p[x]) + 1);
		ft_strlcat(fcmd, cmd, ft_strlen(fcmd) + cmdlen + 2);
		fd = open(fcmd, O_RDONLY);
		if (fd != -1)
		{
			arrayfree(p);
			close(fd);
			return (fcmd);
		}
		zerofree(fcmd);
	}
	error_system(-1, cmd + 1);
	if (x > 0)
	{
		arrayfree(p);
		zerofree(fcmd);
	}
	return (NULL);
}

static char	*make_pathed(char *str, t_list *env)
{
	int		x;
	int		y;
	char	*cmd;
	char	*fcmd;

	x = 0;
	while (!(str[x] == 0 || str[x] == ' '))
		++x;
	cmd = (char *)ft_calloc(x + 2, sizeof(char));
	check_failed_memory(cmd);
	cmd[0] = '/';
	x = 0;
	y = 0;
	while (!(str[x] == 0 || str[x] == ' '))
		if (!(str[x] == 34 || str[x] == 39))
			cmd[++y] = str[x++];
	fcmd = find_real_cmd(cmd, ft_strlen(cmd), unpack_path(env));
	zerofree(cmd);
	return (fcmd);
}

static char	**concatenate(t_list *list)
{
	int		x;
	char	**commands;
	t_list	*args;
	t_list	*lstfree;

	args = list;
	x = ft_lstsize(list);
	commands = (char **)ft_calloc(x + 1, sizeof(char *));
	check_failed_memory(commands);
	x = 0;
	while (args != NULL)
	{
		if (x > 0)
			free(lstfree);
		commands[x] = (char *)args->content;
		lstfree = args;
		args = args->next;
		++x;
	}
	if (x > 0)
		free(lstfree);
	return (commands);
}

char	**ms_fullparse(char *raw, t_list *env)
{
	t_list	*list;
	char	*str;

	if (ft_strlen(raw) == 0)
		return (NULL);
	zerofree(raw);
	while (*str == ' ')
		++str;
	list = ft_lstnew(make_pathed(str, env));
	check_failed_memory(list);
	while (!(*str == 0 || *str == ' '))
		++str;
	while (*str == ' ')
		++str;
	if (*str == 0)
		return (concatenate(list));
	do_the_rest(list, str);
	free(str);
	return (concatenate(list));
}
