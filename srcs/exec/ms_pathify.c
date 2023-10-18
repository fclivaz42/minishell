/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pathify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:10:12 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 19:50:03 by fclivaz          ###    LAUSANNE.CH      */
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
	pathvars = memchk(ft_split(path, ':'));
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
	if (p == NULL)
		return (NULL);
	while (p[++x] != NULL)
	{
		fcmd = (char *)memchk(ft_calloc(cmdlen + \
			ft_strlen(p[x]) + 1, sizeof(char)));
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
	if (x > 0)
		arrayfree(p);
	return (NULL);
}

char	*make_pathed(char *str, t_list *env)
{
	char	*cmd;
	char	*fcmd;

	cmd = (char *)memchk(ft_calloc(ft_strlen(str) + 2, sizeof(char)));
	cmd[0] = '/';
	quicc_copy(cmd, str);
	fcmd = find_real_cmd(cmd, ft_strlen(cmd), unpack_path(env));
	zerofree(cmd);
	if (fcmd != NULL)
	{
		free(str);
		return (fcmd);
	}
	else
		return (str);
}
