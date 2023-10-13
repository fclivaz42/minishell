/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:15:40 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/13 18:45:23 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_list	*move_list(t_list *nlst)
{
	t_list	*hold;
	char	*test;

	test = nlst->content;
	if (!ft_strchr("<|>", test[0]))
	{
		if (nlst->next != NULL)
			test = nlst->next->content;
		while (!ft_strchr("<|>", test[0]))
		{
			nlst = nlst->next;
			if (nlst == NULL)
				return (NULL);
			if (nlst->next == NULL)
				break ;
			test = nlst->next->content;
		}
	}
	hold = nlst->next;
	nlst->next = NULL;
	return (hold);
}

static void	add_tkn(t_token **tkn, t_token *nwtkn)
{
	t_token	*run;

	run = *tkn;
	while (run->next != NULL)
		run = run->next;
	run->next = nwtkn;
	nwtkn->prev = run;
}

static t_token	*mktoken(t_list *lst)
{
	t_token	*tkn;

	tkn = memchk(ft_calloc(1, sizeof(t_token)));
	tkn->fd_in = STDIN_FILENO;
	tkn->fd_out = STDOUT_FILENO;
	tkn->words = lst;
	return (tkn);
}

static t_token	*piped_command(t_minishell *msdata, t_list *nlst, int *valid)
{
	t_token	*tkn;
	int		x;

	x = 0;
	while (nlst != NULL)
	{
		if (x == 0)
			tkn = mktoken(nlst);
		else
			add_tkn(&tkn, mktoken(nlst));
		nlst = move_list(nlst);
		++x;
	}
	return (pipework(msdata, tkn, valid));
}

t_token	*tokenifier(char *rl, t_minishell *msdata, int *valid)
{
	t_list	*parsed;
	t_list	*words;
	char	*test;

	parsed = interparse(rl, msdata->env);
	words = parsed;
	while (parsed != NULL)
	{
		test = parsed->content;
		if (ft_strchr("<|>", test[0]))
			return (piped_command(msdata, words, valid));
		parsed = parsed->next;
	}
	return (mktoken(words));
}
