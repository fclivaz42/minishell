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

char	**list_to_char(t_list *env)
{
	char	**ret;
	char	**tmp;
	char	*var;
	int		x;

	x = -1;
	ret = (char **)ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	check_failed_memory(ret);
	while (env != NULL)
	{
		tmp = (char **)env->content;
		var = (char *)ft_calloc(ft_strlen(tmp[0]) + \
			ft_strlen(tmp[1]) + 2, sizeof(char));
		check_failed_memory(var);
		quicc_copy(var, tmp[0]);
		quicc_copy(var, "=");
		quicc_copy(var, tmp[1]);
		ret[++x] = var;
		env = env->next;
	}
	return (ret);
}

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
