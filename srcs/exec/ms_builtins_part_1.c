/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_part_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:15:33 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/21 20:41:23 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo(t_token *tkn)
{
	t_list	*print;

	print = tkn->words->next;
	if (ft_strncmp(print->content, "-n", 2))
		print = print->next;
	while (print != NULL)
	{
		ft_putstr_fd(print->content, tkn->fd_out);
		print = print->next;
		if (print != NULL)
			write(tkn->fd_out, " ", 1);
	}
	if (ft_strncmp(tkn->words->content, "-n", 2))
		write(tkn->fd_out, "\n", 1);
	return (0);
}
