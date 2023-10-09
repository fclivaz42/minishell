/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:27:28 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/09 20:57:01 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*squigglify(t_list *env, char *pwd)
{
	char	*home;
	char	*squiggled;

	home = find_env(env, "HOME");
	if (home == NULL)
		return (memchk(ft_strdup(pwd)));
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (memchk(ft_strdup(pwd)));
	pwd = pwd + ft_strlen(home);
	squiggled = (char *)memchk(ft_calloc(ft_strlen(pwd) + 2, sizeof(char)));
	ft_strlcpy(squiggled, "~", 2);
	quicc_copy(squiggled, pwd);
	return (squiggled);
}

static void	build_prompt(int ecode, char *prompt, char **vars)
{
	quicc_copy(prompt, "[");
	quicc_copy(prompt, CPRP);
	if (vars[0] != NULL)
		quicc_copy(prompt, vars[0]);
	quicc_copy(prompt, RSET);
	quicc_copy(prompt, " @ ");
	quicc_copy(prompt, CGLD);
	if (vars[1] != NULL)
		quicc_copy(prompt, vars[1]);
	quicc_copy(prompt, RSET);
	quicc_copy(prompt, "]-[");
	quicc_copy(prompt, CBLU);
	if (vars[2] != NULL)
		quicc_copy(prompt, vars[2]);
	quicc_copy(prompt, RSET);
	quicc_copy(prompt, "]");
	if (ecode == 0)
		quicc_copy(prompt, EGRN);
	else
		quicc_copy(prompt, ERED);
	zerofree(vars[2]);
}

static int	calculate_len(char **vars)
{
	int	x;
	int	y;

	y = -1;
	x = ft_strlen("[ @ ]-[]-> ");
	while (++y < 8)
		x = x + ft_strlen(vars[y]);
	x = x + (3 * ft_strlen(RSET));
	return (x);
}

char	*readline_proompter(int ecode, t_list *env, char *pwd)
{
	char	*vars[8];
	char	*prompt;

	vars[0] = find_env(env, "USER");
	vars[1] = find_env(env, HOSTNAME);
	if (pwd != NULL)
		vars[2] = squigglify(env, pwd);
	else
		vars[2] = NULL;
	vars[3] = ERED;
	vars[4] = CPRP;
	vars[5] = CGLD;
	vars[6] = CBLU;
	vars[7] = RSET;
	prompt = (char *)memchk(ft_calloc(calculate_len(vars) + 1, sizeof(char)));
	build_prompt(ecode, prompt, vars);
	if (ecode == 0)
		quicc_copy(prompt, "-> ");
	else
		quicc_copy(prompt, "-x ");
	quicc_copy(prompt, RSET);
	return (prompt);
}
