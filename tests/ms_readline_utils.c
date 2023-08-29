/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:27:28 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/29 15:27:36 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	quicc_copy(char *dest, char *src)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (dest[x] != 0)
		++x;
	while (src[++y] != 0)
		dest[x + y] = src[y];
}

char	*readline_proompter(char *env[])
{
	char	*username;
	char	*hostname;
	char	*workdir;
	char	*prompt;

	username = getenv("USER");
	if (__APPLE__)
		hostname = "iMac";
	else
		hostname = getenv(HOSTNAME);
	workdir = squigglify(getenv("PWD"));
	prompt = (char *)ft_calloc(ft_strlen(username) + \
		ft_strlen(hostname) + ft_strlen(workdir) + \
		ft_strlen("[@]:  >$ ") + 1, sizeof(char));
	quicc_copy(prompt, "[");
	quicc_copy(prompt, username);
	quicc_copy(prompt, "@");
	quicc_copy(prompt, hostname);
	quicc_copy(prompt, "]: ");
	quicc_copy(prompt, workdir);
	quicc_copy(prompt, ">$ ");
	zerofree(workdir);
	return (prompt);
}
