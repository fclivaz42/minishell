/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/30 20:36:08 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*argmaker(char *line)
{
	char	*arg;
	int	x = 0;

	while (!(line[x] == ' ' || line[x] == 0))
		++x;
	arg = (char *)memchk(ft_calloc(x + 1, sizeof(char)));
	x = 0;
	while (!(line[x] == ' ' || line[x] == 0))
	{
		arg[x] = line[x];
		++x;
	}
	return (arg);
}

t_token	*stupid_fucking_parse(char *line, t_list *env)
{
	t_token	*balls;
	short	x = 0;

	(void)env;
	balls = memchk(ft_calloc(1, sizeof(t_token)));
	balls->fd_in = 0;
	balls->fd_out = 1;
	while (*line != 0)
	{
		if (x == 0)
			balls->words = memchk(ft_lstnew(argmaker(line)));
		else
			ft_lstadd_back(&balls->words, memchk(ft_lstnew(argmaker(line))));
		while (!(*line == ' ' || *line == 0))
			++line;
		while (!(*line != ' ' || *line == 0))
			++line;
		++x;
	}
	return (balls);
}

static void	mshell_loop(t_minishell *msdata)
{
	char		*prompt;
	char		*rl;

	while (1)
	{
		prompt = readline_proompter(msdata->env, msdata->pwd);
		rl = memchk(readline(prompt));
		if (ft_strlen(rl) > 0)
		{
			add_history(rl);
			msdata->commands = stupid_fucking_parse(rl, msdata->env);
			g_exit_code = execute(msdata->commands, msdata);
			zerofree(prompt);
			zerofree(rl);
			free_token(msdata->commands);
		}
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_minishell	*msdata;	

	(void)ac;
	(void)av;
	g_exit_code = 0;
	msdata = memchk(ft_calloc(1, sizeof(t_minishell)));
	init_mshell(env, msdata);
	mshell_loop(msdata);
	return (0);
}
