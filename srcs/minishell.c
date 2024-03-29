/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/18 21:37:45 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	tknprint(t_token *tkn)
{
	int		x;
	t_list	*print;

	x = 0;
	while (tkn != NULL)
	{
		printf("DATA FOR TOKEN %d WITH ADDR %p:\n", x, tkn);
		printf("PID_T: %d\n", tkn->pid);
		printf("FD IN: %d\n", tkn->fd_in);
		printf("FD OUT: %d\n", tkn->fd_out);
		printf("WORDS: \n");
		print = tkn->words;
		while (print != NULL)
		{
			tknprint(msdata->commands);
			ft_printf("%s%s ", CBBL, print->content);
			print = print->next;
		}
		ft_putendl_fd(RSET, 1);
		printf("PREV TOKEN: %p\n", tkn->prev);
		printf("NEXT TOKEN: %p\n", tkn->next);
		ft_putendl_fd("", 1);
		tkn = tkn->next;
		++x;
	}
}
*/
static void	signalis(void)
{
	struct sigaction	sigquit;
	struct sigaction	sigint;

	sigint.sa_handler = &interrupt;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sigquit, NULL);
}

static int	validator(char *rl, t_minishell *msdata)
{
	char	c;
	char	*str;

	if (rl == NULL)
		freexit(msdata);
	if (ft_strlen(rl) == 0)
		return (1);
	str = rl;
	while (*rl)
	{
		if (ft_strchr(":&*{}^[]()\\;%~`!#", *rl))
			return (error_unsupported_character(*rl, msdata));
		if (*rl == 34 || *rl == 39)
		{
			c = *rl;
			++rl;
			while (!(*rl == c || *rl == 0))
				++rl;
			if (*rl == 0)
				return (error_bad_format(str, msdata));
		}
		++rl;
	}
	return (0);
}

static void	reset(t_minishell *msdata, char *rl, char *prompt, int valid)
{
	char	*ecopy;

	ecopy = ft_itoa(msdata->ecode);
	if (find_env(msdata->env, "?"))
		replace_env(msdata->env, "?", ecopy);
	else
		new_env_var(msdata, "?", ecopy);
	zerofree(rl);
	zerofree(ecopy);
	zerofree(prompt);
	if (!valid)
		clear_tokens(msdata->commands);
	msdata->commands = NULL;
	msdata->forked = 0;
}

static void	mshell_loop(t_minishell *msdata)
{
	char	*prompt;
	char	*rl;
	int		valid;

	valid = 1;
	while (1)
	{
		prompt = readline_proompter(msdata->ecode, \
			msdata->env, msdata->pwd);
		signalis();
		rl = readline(prompt);
		valid = validator(rl, msdata);
		if (ft_strlen(rl) > 0)
			add_history(rl);
		if (!valid)
		{
			sigtochild();
			msdata->commands = tokenifier(rl, msdata, &valid);
			if (!valid)
				execute(msdata->commands, msdata);
		}
		reset(msdata, rl, prompt, valid);
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_minishell	*msdata;

	(void)ac;
	msdata = memchk(ft_calloc(1, sizeof(t_minishell)));
	msdata->ecode = 0;
	init_mshell(av[0], env, msdata);
	mshell_loop(msdata);
	return (0);
}
