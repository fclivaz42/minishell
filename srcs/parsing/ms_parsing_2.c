/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:23:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 20:33:07 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_quotes(char *str, t_list *env, int *size, char q)
{
	int		s;
	int		x;

	s = 0;
	x = 0;
	while (str[++x] != q)
	{
		if (str[x] == '$' && q == 34)
			x = x + expand_var(&str[x], env, &s);
		if (str[x] == q)
			break ;
		++s;
	}
	*size = *size + s - 1;
	return (x);
}

int	copy_quotes(char *ntrp, char *str, t_list *env, char q)
{
	int		x;
	int		y;
	int		len;

	len = count_quotes(str, env, &x, q);
	x = -1;
	y = 0;
	++str;
	while (str[++x] != q)
	{
		if (str[x] == '$' && q == 34)
		{
			x = x + copy_var(&ntrp[y], &str[x], env);
			while (ntrp[y] != 0)
				++y;
		}
		else
			ntrp[y++] = str[x];
		if (str[x] == q)
			break ;
	}
	return (len + 1);
}

int	expand_var(char *str, t_list *env, int *size)
{
	int		x;
	char	c;
	char	*var;

	x = 0;
	++str;
	var = str;
	while (ft_isalnum(str[x]) || str[x] == '?')
		++x;
	c = str[x];
	str[x] = 0;
	if (find_env(env, var))
		*size = *size + ft_strlen(find_env(env, var)) + 1;
	str[x] = c;
	return (x);
}

int	copy_var(char *ntrp, char *str, t_list *env)
{
	int		x;
	char	c;
	char	*var;

	x = 0;
	++str;
	var = str;
	while (ft_isalnum(str[x]) || str[x] == '?')
		++x;
	c = str[x];
	str[x] = 0;
	if (find_env(env, var))
		quicc_copy(ntrp, find_env(env, var));
	while (*ntrp != 0)
		++ntrp;
	str[x] = c;
	ntrp[0] = 0;
	return (x);
}
