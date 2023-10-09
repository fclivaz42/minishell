/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tkpiping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:15:40 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/09 22:54:00 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	piping_work(t_token *tkn1, t_list *nlst)
{
	t_token	*tkn;

	tkn = memchk(ft_calloc(1, sizeof(t_token)));
}

t_token	*tokenifier(char *rl, t_list *env)
{
	t_list	*parsed;
	t_token	*tkn;
	char	*test;

	tkn = memchk(ft_calloc(1, sizeof(t_token)));
	tkn->fd_in = 0;
	tkn->fd_out = 1;
	tkn->words = interparse(rl, env);
	parsed = tkn->words;
	while (parsed != NULL)
	{
		test = parsed->content;
		if (ft_strchr("<|>", test[0]))
			piping_work(tkn, parsed->next);
		parsed = parsed->next;
	}
	return (tkn);
}
