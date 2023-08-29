/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_new_tokenifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:23:36 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/29 15:23:45 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*append_argument(t_list *list, char *str)
{
	t_list	*append;
	char	*argument;
	char	c;
	int		len;

	c = str[0];
	len = 0;
	if (c == 34 || c == 39)
	{
		++str;
		while (!(str[len] == 34 || str[len] == 39 || str[len] == 0))
			++len;
	}
	else
		while (!(str[len] == ' ' || str[len] == 0))
			++len;
	argument = (char *)ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(argument, str, len + 1);
	return (ft_lstnew(argument));
}

void	do_the_rest(t_list *list, char *str)
{
	char	c;
	
	while (*str != 0)
	{
		ft_lstadd_back(&list, append_argument(list, str));
		c = str[0];
		if (c == 34 || c == 39)
		{
			++str;
			while (!(*str == 34 || *str == 39))
				ft_putchar_fd(*str++, 1);
			++str;
		}
		else
			while (!(*str == ' ' || *str == 0))
				++str;
		while (*str == ' ')
			++str;
	}
}
