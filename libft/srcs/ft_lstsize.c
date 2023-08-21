/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:12:41 by fclivaz           #+#    #+#             */
/*   Updated: 2023/04/17 19:12:52 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		size;

	size = 0;
	if (!lst)
		return (0);
	temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
		++size;
	}
	++size;
	return (size);
}
