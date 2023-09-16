/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:27 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/16 17:54:36 by fclivaz          ###   ########.fr       */
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
	char	*ntrp;
	char	*cmd;
	char	*fcmd;

	x = 0;
	while (!(ft_strchr(" \t\n\0", str[x])))
		++x;
	cmd = (char *)ft_calloc(x + 2, sizeof(char));
	check_failed_memory(cmd);
	cmd[0] = '/';
	x = 0;
	while (!(ft_strchr(" \t\n\0", str[x])))
		++x;
	interpreter((str + x), env, str[x]);
	fcmd = find_real_cmd(cmd, ft_strlen(cmd), unpack_path(env));
	zerofree(cmd);
	return (fcmd);
}

t_list	*ms_fullparse(char *str, t_list *env)
{
	t_list	*list;

	if (ft_strlen(str) == 0)
		return (NULL);
	while (ft_strchr(" \t\n\0", *str))
		++str;
	list = ft_lstnew(make_pathed(str, env));
	check_failed_memory(list);
	while (!(*str == 0 || *str == ' '))
		++str;
	while (*str == ' ')
		++str;
	if (*str == 0)
		return (list);
	do_the_rest(list, str);
	return (list);
}
