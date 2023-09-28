/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_interpreter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:23:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/28 22:47:15 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	find_var_size(t_list *env, char *raw)
{
	int		size;
	char	*var;

	size = 0;
	while (!(*raw == ' ' || *raw == 0 || *raw == 34))
	{
		++size;
		++raw;
	}
	var = (char *)memchk(ft_calloc(size + 1, sizeof(char)));
	ft_strlcpy(var, raw - size, size + 1);
	size = ft_strlen(find_env(env, var));
	zerofree(var);
	return (size);
}

static int	find_size(char *raw, t_list *env)
{
	int		size;

	size = 0;
	while (*raw != 0)
	{
		if (*raw == 39)
		{
			++raw;
			while (*raw != 39)
			{
				++size;
				++raw;
			}
		}
		if (*raw == '$')
		{
			++raw;
			size = size + find_var_size(env, raw);
			while (!(*raw == ' ' || *raw == 0 || *raw == 34))
				++raw;
		}
	++raw;
	++size;
	}
	ft_printf("size is %d\n", size);
	return (size);
}

char	*interpreter(char *raw, t_list *env, char mode)
{
	int		i;
	char	*ntrp;

	i = 0;
	ntrp = (char *)memchk(ft_calloc(find_size(raw, env) + 1, sizeof(char)));
	while (*raw != 0)
	{
		if (*raw == 39)
		{
			++raw;
			while (*raw != 39)
				ntrp[i++] = *raw++;
			++raw;
		}
	ntrp[i++] = raw[0];
	++raw;
	}
	printf("returning %s\n", ntrp);
	return (ntrp);
}
