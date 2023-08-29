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
	int		x = -1;
	char	**commands;
	char	*prompt;
	char	*rl;
	int		pid;

//	pid = fork();
//	if (pid == 0)
//		clear_term(env);
//	waitpid(pid, NULL, 0);
	printf("\nWelcome to minishell alpha v0.25!\n\n");
	prompt = readline_proompter(env);
	rl = readline(prompt);
	commands = ms_fullparse(rl);
	execute(commands, env);
//	while (commands[++x] != NULL)
//		printf("command %d is: %s\n", x, commands[x]);
	arrayfree(commands);
	zerofree(prompt);
	zerofree(rl);
	return (0);
}