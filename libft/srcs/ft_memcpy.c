/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:21:40 by fclivaz           #+#    #+#             */
/*   Updated: 2022/10/20 18:31:00 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	x;	

	x = 0;
	if (src == dest || n == 0)
		return (dest);
	if (!src && !dest)
		return (0);
	while (x != n)
	{
		((unsigned char *)dest)[x] = ((unsigned char *)src)[x];
		x++;
	}	
	return (dest);
}
