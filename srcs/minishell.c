/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/09 20:48:42 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>

static int	validator(char *rl, t_minishell *msdata)
{
	char	c;
	char	*str;

	if (ft_strlen(rl) == 0)
		return (1);
	str = rl;
	while (*rl)
	{
		if (ft_strchr("<>:&*{}^[]()\\;%~`!#", *rl))
			return (!error_unsupported_character(*rl, msdata));
		if (*rl == 34 || *rl == 39)
		{
			c = *rl;
			++rl;
			while (!(*rl == c || *rl == 0))
				++rl;
			if (*rl == 0)
				return (!error_bad_format(str, msdata));
		}
		++rl;
	}
	return (0);
}

static void	mshell_loop(t_minishell *msdata)
{
	char	*prompt;
	char	*rl;
	char	*ecopy;

	while (1)
	{
		prompt = readline_proompter(msdata->ecode, \
			msdata->env, msdata->pwd);
		rl = memchk(readline(prompt));
		if (!validator(rl, msdata))
		{
			add_history(rl);
			msdata->commands = tokenifier(rl, msdata->env);
			msdata->ecode = execute(msdata->commands, msdata);
			waitpid(msdata->pid, &msdata->ecode, 0);
		}
		ecopy = ft_itoa(msdata->ecode);
		if (find_env(msdata->env, "?"))
			replace_env(msdata->env, "?", ecopy);
		else
			new_env_var(msdata, "?", ecopy);
		reset(msdata->commands, rl, prompt, ecopy);
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
