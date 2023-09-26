/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_part_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:15:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/26 20:11:05 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo(t_token *tkn)
{
	t_list	*print;

	print = tkn->words->next;
	if (ft_strncmp(print->content, "-n", 2))
		print = print->next;
	while (print != NULL)
	{
		ft_putstr_fd(print->content, tkn->fd_out);
		print = print->next;
		if (print != NULL)
			write(tkn->fd_out, " ", 1);
	}
	if (ft_strncmp(tkn->words->content, "-n", 2))
		write(tkn->fd_out, "\n", 1);
	return (0);
}

static char	*relative_dir(char *path, char *pwd)
{
	char	*new_dir;
	int		x;
	int		y;
	// --- USE SPLIT AND CHAR ** FOR INDEXATION
	x = 0;
	if (path[0] != '.')
		new_dir
	return (new_dir);
}

int	cd(t_token *tkn, t_minishell *msdata)
{
	int		fd;
	char	*path;
	char	*new_dir;

	path = tkn->words->next->content;
	if (path[0] != '/')
		new_dir = relative_dir(path, msdata->pwd);
	else
		new_dir = ft_strdup(path);
	check_failed_memory(new_dir);
	fd = open(new_dir, O_RDONLY);
	if (fd <= 0)
		error_system(2 , new_dir);
	else
	{
		zerofree(msdata->pwd);
		msdata->pwd = ft_strdup(new_dir);
		check_failed_memory(msdata->pwd); 
		if (find_env(msdata->env, "PWD") != NULL)
			replace_env(msdata->env, "PWD", new_dir);
		else
			new_env_var(msdata->env, "PWD", new_dir);
	}
	free(new_dir);
	return (0);
}
