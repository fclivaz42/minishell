/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 19:58:14 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/31 19:58:22 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*find_env(t_list *env, char *str)
{
	t_list	*list;
	char	**test;

	list = env;
	test = (char **)list->content;
	while(ft_strncmp(str, test[0], ft_strlen(test[0])))
	{
		list = list->next;
		if (list == NULL)
			return (NULL);
		test = (char **)list->content;
	}
	return (list);
}


void	replace_env(t_list *env, char *str)
{
	char	**var;

	var = (char **)env->content;
	zerofree(var[1]);
	var[1] = ft_strdup(str);
	check_failed_memory(var[1]);
}

void	delete_env(t_list *env, char *str)
{
	t_list	*delete;
	t_list	*prev;
	char	**test;
	
	delete = env;
	test = (char **)delete->content;
	while(ft_strncmp(str, test[0], ft_strlen(test[0])))
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

t_list	*copy_env(char *env[])
{
	int		x;
	int		len;
	char	**var;
	t_list	*newenv;

	x = -1;
	while (env[++x] != NULL)
	{
		var = (char **)ft_calloc(3, sizeof(char *));
		check_failed_memory(var);
		len = ft_strlen(env[x]) - ft_strlen(ft_strchr(env[x], '='));
		var[0] = (char *)ft_calloc(len + 1, sizeof(char));
		check_failed_memory(var[0]);
		ft_strlcpy(var[0], env[x], len + 1);
		var[1] = ft_strdup(ft_strchr(env[x], '=') + 1);
		check_failed_memory(var[1]);
		if (x == 0)
			newenv = ft_lstnew(var);
		if (x > 0)
			ft_lstadd_back(&newenv, ft_lstnew(var));
	}
	return (newenv);
}