/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:25:00 by fclivaz           #+#    #+#             */
/*   Updated: 2023/04/17 17:25:07 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lnk;

	lnk = malloc(sizeof(t_list));
	if (!lnk)
		return (NULL);
	lnk->content = content;
	lnk->next = NULL;
	return (lnk);
}
