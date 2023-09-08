/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_new_tokenifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:23:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/08 20:10:28 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_size(char *raw, t_list *env)
{
	int	size;

	size = 0;
	while (*raw != 0)
	{
		if (*raw == 39)
		{
			++raw;
			while (*raw++ != 39)
				++size;
		}
		if (*raw == '$')
		{
			size = size + ft_strlen(find_env(env, ++raw)); 
			printf("Found in RAW: %s\n", raw);
			while(!(*raw == ' ' || *raw == 0 || *raw == 34))
				++raw;
		}
	++raw;
	++size;
	}
	ft_printf("found LEN %d\n", size);
	return (size);
}

char	*interpreter(char *raw, t_list *env)
{
	int		i;
	char	*procs;

	i = 0;
	procs = (char *)ft_calloc(find_size(raw, env) + 1, sizeof(char));
	ft_putendl_fd(raw, 1);
	while (*raw != 0)
	{
		if (*raw == 39)
		{
			printf("balls");
		}
	procs[i++] = raw[0];
	++raw;
	}
	printf("returning %s\n", procs);
	return (procs);
}

t_list	*append_argument(t_list *list, char *str)
{
	t_list	*append;
	char	*argument;
	char	c;
	int		len;

	c = str[0];
	len = 0;
	if (c == 34 || c == 39)
	{
		++str;
		while (!(str[len] == 34 || str[len] == 39 || str[len] == 0))
			++len;
	}
	else
		while (!(str[len] == ' ' || str[len] == 0))
			++len;
	argument = (char *)ft_calloc(len + 1, sizeof(char));
	check_failed_memory(argument);
	ft_strlcpy(argument, str, len + 1);
	return (ft_lstnew(argument));
}

void	do_the_rest(t_list *list, char *str)
{
	char	c;

	while (*str != 0)
	{
		ft_lstadd_back(&list, append_argument(list, str));
		c = str[0];
		if (c == 34 || c == 39)
		{
			++str;
			while (!(*str == 34 || *str == 39))
				str++;
			++str;
		}
		else
			while (!(*str == ' ' || *str == 0))
				++str;
		while (*str == ' ')
			++str;
	}
}
