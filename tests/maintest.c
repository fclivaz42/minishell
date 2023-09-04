/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/24 16:44:49 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *env[])
{
	int			x = -1;
	char		**commands;
	char		*prompt;
	char		*rl;
	int			pid;
	t_minishell	msdata;	

//	pid = fork();
//	if (pid == 0)
//		clear_term(env);
//	waitpid(pid, NULL, 0);
	msdata.env = copy_env(env);
	printf("\nWelcome to minishell alpha v0.25!\n\n");
	prompt = readline_proompter(msdata.env);
	rl = readline(prompt);
	commands = ms_fullparse(rl, msdata.env);
	execute(commands, msdata.env);
//	while (commands[++x] != NULL)
//		printf("command %d is: %s\n", x, commands[x]);
	arrayfree(commands);
	zerofree(prompt);
	zerofree(rl);
	return (0);
}