/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:25:00 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/04 16:04:01 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lnk;

	lnk = ft_calloc(1, sizeof(t_list));
	if (!lnk)
		return (NULL);
	lnk->content = content;
	lnk->next = NULL;
	return (lnk);
}
