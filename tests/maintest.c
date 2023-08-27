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

void	zerofree(char *s)
{
	ft_bzero(s, ft_strlen(s));
	free(s);
}

void	arrayfree(char **arr)
{
	int		x;

	x = -1;
	while (arr[++x] != NULL)
		zerofree(arr[x]);
	free(arr);
}

static char	*squigglify(char *pwd)
{
	char	*home;
	char	*squiggled;

	home = getenv("HOME");
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (pwd);
	pwd = pwd + ft_strlen(home);
	squiggled = (char *)ft_calloc(ft_strlen(pwd) + 2, sizeof(char));
	ft_strlcpy(squiggled, "~", 2);
	ft_strlcat(squiggled, pwd, ft_strlen(pwd) + 2);
	return (squiggled);
}

char	*readline_proompter()
{
	char	*username;
	char	*hostname;
	char	*workdir;
	char	*prompt;

	username = getenv("USER");
	hostname = getenv(HOSTNAME);
	workdir = squigglify(getenv("PWD"));
	prompt = (char *)ft_calloc(ft_strlen(username) + \
		ft_strlen(hostname) + ft_strlen(workdir) + \
		ft_strlen("[@]:  >$ ") + 1, sizeof(char));
	ft_strlcpy(prompt, "[", 2);
	ft_strlcat(prompt, username, ft_strlen(prompt) + ft_strlen(username) + 2);
	ft_strlcat(prompt, "@", ft_strlen(prompt) + 2);
	ft_strlcat(prompt, hostname, ft_strlen(prompt) + ft_strlen(hostname) + 2);
	ft_strlcat(prompt, "]: ", ft_strlen(prompt) + 4);
	ft_strlcat(prompt, workdir, ft_strlen(prompt) + ft_strlen(workdir) + 2);
	ft_strlcat(prompt, ">$ ", ft_strlen(prompt) + 4);
	free(workdir);
	return(prompt);
}

static void	clear_term(char *env[])
{
	char	**exec;

	exec = ms_fullparse("clear");
	execve(exec[0], exec, env);
}

int	main(int ac, char *av[], char *env[])
{
	int		x = -1;
	char	**commands;
	char	*prompt;
	int		pid;

	pid = fork();
	if (pid == 0)
		clear_term(env);
	printf("\nWelcome to minishell v0.5!\n\n");
	prompt = readline_proompter();
	commands = ms_fullparse(readline(prompt));
	while (commands[++x] != NULL)
		printf("command %d is: %s\n", x, commands[x]);
	arrayfree(commands);
	zerofree(prompt);
	return (0);
}