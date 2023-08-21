/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:47:46 by fclivaz           #+#    #+#             */
/*   Updated: 2023/04/17 20:47:57 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cool;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		(*del)((*lst)->content);
		cool = (*lst)->next;
		free(*lst);
		*lst = cool;
	}
	lst = NULL;
}
