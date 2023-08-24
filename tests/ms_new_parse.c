/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_new_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/24 16:40:33 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**unpack_path(char *env[])
{
	int		id;
	char	*path;
	char	**pathvars;

	id = -1;
	while (env[++id] != NULL)
		if (!ft_strncmp(env[id], "PATH=", 5))
			path = ft_strchr(env[id], '/');
	pathvars = ft_split(path, ':');
	check_failed_memory(pathvars);
	id = -1;
	while (pathvars[++id] != NULL)
		if (pathvars[id][ft_strlen(pathvars[id])] == '/')
			pathvars[id][ft_strlen(pathvars[id])] = 0;
	return (pathvars);
}

static char	*find_real_cmd(char *cmd, int cmdlen, char **p)
{
	int		x;
	char	*fcmd;

	x = -1;
	while (p[++x] != NULL)
	{
		fcmd = (char *)ft_calloc(cmdlen + ft_strlen(p[x]) + 1, sizeof(char));
		check_failed_memory(fcmd);
		ft_strlcpy(fcmd, p[x], ft_strlen(p[x]) + 1);
		ft_strlcat(fcmd, cmd, ft_strlen(p[x]) + cmdlen + 2);
		if (open(fcmd, O_RDONLY) != -1)
		{
			arrayfree(p);
			return (fcmd);
		}
		free(cmd);
		free(fcmd);
	}
	error_system(-1, cmd + 1);
	free(fcmd);
	return (NULL);
}

static char	*make_pathed(char *str, char *env[])
{
	int		x;
	char	*cmd;

	x = 0;
	while (*str == ' ')
		str++;
	while (!(str[x] == 0 || str[x] == ' '))
		++x;
	cmd = (char *)ft_calloc(x + 2, sizeof(char));
	check_failed_memory(cmd);
	cmd[0] = '/';
	ft_strlcat(cmd, str, x + 1);
	return (find_real_cmd(cmd, ft_strlen(cmd), unpack_path(env)));
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
	free(lstfree);
	return (commands);
}

char	**ms_fullparse(char *str, char *env[])
{
	t_list	*list;

	list = ft_lstnew(make_pathed(str, env));
//	ft_lstadd_back(&list, separator(str));
	return (concatenate(list));
}
