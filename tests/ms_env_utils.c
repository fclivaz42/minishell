/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:58:14 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/07 18:00:20 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_env_var(t_list *env, char *newvar, char *value)
{
	t_list	*addition;
	char	**fullenv;

	fullenv = (char
		**)ft_calloc(3, sizeof(char **));
	fullenv[0] = ft_strdup(newvar);
	fullenv[1] = ft_strdup(value);
	ft_lstadd_back(&env, ft_lstnew(fullenv));
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
	while (ft_strncmp(str, test[0], len))
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
	while (ft_strncmp(var_to_change, var[0], ft_strlen(var[0])))
	{
		list = list->next;
		if (list == NULL)
			return ;
		var = (char **)list->content;
	}
	zerofree(var[1]);
	var[1] = ft_strdup(new_var);
	check_failed_memory(var[1]);
}

void	delete_env(t_list *env, char *str)
{
	t_list	*delete;
	t_list	*prev;
	char	**test;

	delete = env;
	test = (char **)delete->content;
	while (ft_strncmp(str, test[0], ft_strlen(test[0])))
	{
		prev = delete;
		delete = delete->next;
		if (delete == NULL)
			return ;
		test = (char **)delete->content;
	}
	prev->next = delete->next;
	arrayfree((char **)delete->content);
	free(delete);
}
