/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:15:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/30 21:51:45 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo(t_token *tkn)
{
	t_list	*print;

	if (tkn->words->next == NULL)
		return (write(tkn->fd_out, "\n", 1));
	print = tkn->words->next;
	if (!ft_strncmp(print->content, "-n", 2))
		print = print->next;
	while (print != NULL)
	{
		ft_putstr_fd(print->content, tkn->fd_out);
		print = print->next;
		if (print != NULL)
			write(tkn->fd_out, " ", 1);
	}
	if (ft_strncmp(tkn->words->next->content, "-n", 2))
		write(tkn->fd_out, "\n", 1);
	return (0);
}

static void	comparison_moment(char *new_dir, char *rw, char *path)
{
	int	x;

	x = -1;
	if (!ft_strncmp(path, "..", ft_strlen(path) + 1) && rw != new_dir)
	{
		rw = ft_strrchr(new_dir, '/');
		if (rw != new_dir)
			while (rw[++x] != 0)
				rw[x] = 0;
		else
			ft_bzero(rw + 1, 1024);
	}
	else if (!ft_strncmp(path, ".", ft_strlen(path) + 1))
		rw = rw;
	else
	{
		rw = ft_strchr(new_dir, 0);
		--rw;
		if (*rw != '/')
			rw[1] = '/';
		while (*rw != 0)
			++rw;
		quicc_copy(rw, path);
	}
}

char	*relative_dir(char **path, char *pwd)
{
	char	*new_dir;
	char	*rw;
	int		x;

	x = -1;
	new_dir = (char *)memchk(ft_calloc(1025, sizeof(char)));
	quicc_copy(new_dir, pwd);
	rw = ft_strchr(new_dir, 0);
	while (path[++x] != 0)
		comparison_moment(new_dir, rw, path[x]);
	arrayfree(path);
	rw = memchk(ft_strdup(new_dir));
	zerofree(new_dir);
	return (rw);
}

static int	update_pwd(char *new_dir, t_minishell *msdata)
{
	chdir(new_dir);
	if (find_env(msdata->env, "OLDPWD") != NULL)
		replace_env(msdata->env, "OLDPWD", msdata->pwd);
	else
		new_env_var(msdata, "OLDPWD", msdata->pwd);
	zerofree(msdata->pwd);
	msdata->pwd = memchk(ft_strdup(new_dir));
	if (find_env(msdata->env, "PWD") != NULL)
		replace_env(msdata->env, "PWD", new_dir);
	else
		new_env_var(msdata, "PWD", new_dir);
	return (0);
}

int	cd(t_token *tkn, t_minishell *msdata)
{
	DIR		*fd;
	char	*path;
	char	*new_dir;

	if (tkn->words->next == NULL)
		if (!find_env(msdata->env, "HOME"))
			return (1);
	if (tkn->words->next == NULL)
		return (update_pwd(find_env(msdata->env, "HOME"), msdata));
	path = tkn->words->next->content;
	if (path[0] == '/')
		new_dir = memchk(ft_strdup(path));
	else
		new_dir = relative_dir(memchk(ft_split(path, '/')), msdata->pwd);
	fd = opendir(new_dir);
	if (fd == NULL)
		error_system(2, path);
	else
	{
		update_pwd(new_dir, msdata);
		closedir(fd);
	}
	free(new_dir);
	return (0);
}
