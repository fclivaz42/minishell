/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:32:56 by fclivaz           #+#    #+#             */
/*   Updated: 2023/04/17 21:33:06 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cool;
	t_list	*first;

	if (!lst || !f || !del)
		return (NULL);
	first = ft_lstnew((*f)(lst->content));
	if (first == NULL)
		return (NULL);
	cool = first;
	lst = lst->next;
	while (lst != NULL)
	{
		cool->next = ft_lstnew((*f)(lst->content));
		if (cool->next == NULL)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		cool = cool->next;
		lst = lst->next;
	}
	return (first);
}
