/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/14 16:38:37 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	freexit()
{
}

int	main(int ac, char *av[], char *env[])
{
	char		**commands;
	char		*prompt;
	char		*rl;
	t_minishell	msdata;	

	(void)ac;
	(void)av;
//	pid = fork();
//	if (pid == 0)
//		clear_term(env);
//	waitpid(pid, NULL, 0);
	msdata.env = copy_env(env);
	printf("\nWelcome to minishell alpha v0.25!\n\n");
	while (1 == 1)
	{
		prompt = readline_proompter(msdata.env);
		rl = readline(prompt);
		commands = ms_fullparse(rl, msdata.env);
		msdata.pid = fork();
		if (msdata.pid == 0)
			execute(commands, msdata.env);
//		while (commands[++x] != NULL)
//			printf("command %d is: %s\n", x, commands[x]);
		arrayfree(commands);
		zerofree(prompt);
		waitpid(msdata.pid, NULL, 0);
	}
	return (0);
}
