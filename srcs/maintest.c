/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/29 06:02:09 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	free_token(t_token *tkn);

void	freexit(t_minishell *msdata)
{
	t_list	*env;
	t_list	*del;

	env = msdata->env;
	while(env != NULL)
	{
		del = env;
		arrayfree(env->content);
		env = del->next;
		free(del);

	}
	zerofree(msdata->pwd);
	free_token(msdata->commands);
	free(msdata);
	exit(0);
}

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
	t_list	*commands;
	short	x = 0;

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

void	free_token(t_token *tkn)
{
	t_list	*env;
	t_list	*del;

	env = tkn->words;
	while(env != NULL)
	{
		del = env;
		zerofree(env->content);
		env = del->next;
		free(del);
	}
	free(tkn);
}

int	main(int ac, char *av[], char *env[])
{
	char		*prompt;
	char		*rl;
	t_minishell	*msdata;	

	(void)ac;
	(void)av;
	msdata = memchk(ft_calloc(1, sizeof(t_minishell)));
	copy_env(env, msdata);
	if (find_env(msdata->env, "PWD"))
		msdata->pwd = memchk(ft_strdup(find_env(msdata->env, "PWD")));
	printf("\nWelcome to minishell alpha v0.5!\n\n");
	while (1 == 1)
	{
		prompt = readline_proompter(msdata->env, msdata->pwd);
		rl = memchk(readline(prompt));
		msdata->commands = stupid_fucking_parse(rl, msdata->env);
		execute(msdata->commands, msdata);
		zerofree(prompt);
		zerofree(rl);
		free_token(msdata->commands);
	}
	return (0);
}
