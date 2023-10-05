/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interparse_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:44:15 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/05 19:35:16 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_list(t_list *lst)
{
	t_list *cmd;

	cmd = lst;
	while (cmd != NULL)
	{
		ft_putstr_fd("TOKEN IS ", 1);
		ft_putendl_fd(cmd->content, 1);
		cmd = cmd->next;
	}
}


int main(int ac, char *av[], char *env[])
{
	t_list *list;
	char	*rl;
	t_minishell *msdata = memchk(ft_calloc(1, sizeof(t_minishell)));

	(void)ac;
	init_mshell(av[0], env, msdata);
	while (1)
	{
		rl = readline("balls>");
		list = interparse(rl, msdata->env);
		print_list(list);
	}
}
