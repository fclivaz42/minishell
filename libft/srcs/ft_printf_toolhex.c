/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_toolhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:37:28 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/12 15:14:59 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	pr_hex(unsigned int ptr, char str)
{
	if (ptr >= 16)
	{
		pr_hex(ptr / 16, str);
		pr_hex(ptr % 16, str);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
		{
			if (str == 'x')
				ft_putchar_fd((ptr - 10 + 'a'), 1);
			if (str == 'X')
				ft_putchar_fd((ptr - 10 + 'A'), 1);
		}
	}
}

int	print_hex(char str, unsigned int i)
{
	int	ret;

	ret = 0;
	if (i == 0)
		return (write(1, "0", 1));
	pr_hex(i, str);
	while (i != 0)
	{
		++ret;
		i = i / 16;
	}
	return (ret);
}
