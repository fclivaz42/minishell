/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:58:14 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/29 19:20:36 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	new_env_var(t_minishell *msdata, char *newvar, char *value)
{
	char	**fullenv;

	fullenv = (char **)memchk(ft_calloc(3, sizeof(char **)));
	fullenv[0] = memchk(ft_strdup(newvar));
	fullenv[1] = memchk(ft_strdup(value));
	if (msdata->env == NULL)
		msdata->env = memchk(ft_lstnew(fullenv));
	else
		ft_lstadd_back(&msdata->env, memchk(ft_lstnew(fullenv)));
}

char	*find_env(t_list *env, char *str)
{
	t_list	*list;
	char	**test;
	int		len;

	len = 0;
	list = env;
	test = (char **)list->content;
	while (!(str[len] == 0 || str[len] == ' '))
		len++;
	while (ft_strncmp(str, test[0], len + 1))
	{
		list = list->next;
		if (list == NULL)
			return (NULL);
		test = (char **)list->content;
	}
	return (test[1]);
}

void	replace_env(t_list *env, char *var_to_change, char *new_var)
{
	t_list	*list;
	char	**var;

	list = env;
	var = (char **)list->content;
	while (ft_strncmp(var_to_change, var[0], ft_strlen(var[0]) + 1))
	{
		list = list->next;
		if (list == NULL)
			return ;
		var = (char **)list->content;
	}
	zerofree(var[1]);
	var[1] = memchk(ft_strdup(new_var));
}

void	delete_env(t_minishell *msdata, char *str)
{
	t_list	*delete;
	t_list	*prev;
	char	**test;
	int		x;

	x = 0;
	delete = msdata->env;
	prev = msdata->env;
	test = (char **)delete->content;
	while (ft_strncmp(str, test[0], ft_strlen(test[0]) + 1))
	{
		prev = delete;
		delete = delete->next;
		if (delete == NULL)
			return ;
		test = (char **)delete->content;
		++x;
	}
	if (x > 0)
		prev->next = delete->next;
	else
		msdata->env = delete->next;
	arrayfree((char **)delete->content);
	free(delete);
}
